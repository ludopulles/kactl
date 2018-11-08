#!/usr/bin/env python2
# encoding: utf-8

# Source code preprocessor for KACTL building process.
# Written by Håkan Terelius, 2008-11-24

from __future__ import print_function
import hashlib
import sys
import getopt


def escape(input):
    input = input.replace('<', r'\ensuremath{<}')
    input = input.replace('>', r'\ensuremath{>}')
    return input

def pathescape(input):
    input = input.replace('\\', r'\\')
    input = input.replace('_', r'\_')
    input = escape(input)
    return input

def codeescape(input):
    input = input.replace('_', r'\_')
    input = input.replace('\n', '\\\\\n')
    input = input.replace('{', r'\{')
    input = input.replace('}', r'\}')
    input = input.replace('^', r'\ensuremath{\hat{\;}}')
    input = escape(input)
    return input

def ordoescape(input, esc=True):
    if esc:
        input = escape(input)
    start = input.find("O(")
    if start >= 0:
        bracketcount = 1
        end = start+1
        while end+1<len(input) and bracketcount>0:
            end = end + 1
            if input[end] == '(':
                bracketcount = bracketcount + 1
            elif input[end] == ')':
                bracketcount = bracketcount - 1
        if bracketcount == 0:
            return r"%s\bigo{%s}%s" % (input[:start], input[start+2:end], ordoescape(input[end+1:], False))
    return input

def processwithcomments(caption, instream, outstream, lang = 'cpp'):
    knowncommands = ['Author', 'Date', 'Description', 'Source', 'Time', 'Memory', 'License', 'Status', 'Usage']
    requiredcommands = ['Author', 'Description']
    includelist = []
    error = ""
    warning = ""
    # Read lines from source file
    try:
        lines = instream.readlines()
    except:
        error = "Could not read source."
    nlines = list()
    for line in lines:
        had_comment = "///" in line
        # Remove /// comments
        line = line.split("///")[0].rstrip()
        # Remove '#pragma once' and 'using namespace std;' lines
        if line == "#pragma once" or line == "using namespace std;":
            continue
        if line.endswith("/** exclude-line */"):
            continue
        if had_comment and not line:
            continue
        # Check includes
        include = isinclude(line)
        if include is not None:
            includelist.append(include)
            continue
        nlines.append(line)
    # Remove and process /** */ comments
    source = '\n'.join(nlines)
    nsource = ''
    start = source.find("/**")
    end = 0
    commands = {}
    while start >= 0 and not error:
        nsource = nsource.rstrip() + source[end:start]
        end = source.find("*/", start)
        if end<start:
            error = "Invalid /** */ comments."
            break
        comment = source[start+3:end].strip()
        end = end + 2
        start = source.find("/**",end)

        commentlines = comment.split('\n')
        command = None
        value = ""
        for cline in commentlines:
            allow_command = False
            cline = cline.strip()
            if cline.startswith('*'):
                cline = cline[1:].strip()
                allow_command = True
            ind = cline.find(':')
            if allow_command and ind != -1 and ' ' not in cline[:ind]:
                if command:
                    if command not in knowncommands:
                        error = error + "Unknown command: " + command + ". "
                    commands[command] = value.lstrip()
                command = cline[:ind]
                value = cline[ind+1:].strip()
            else:
                value = value + '\n' + cline
        if command:
            if command not in knowncommands:
                error = error + "Unknown command: " + command + ". "
            commands[command] = value.lstrip()
    for rcommand in sorted(set(requiredcommands) - set(commands)):
        error = error + "Missing command: " + rcommand + ". "
    if end>=0:
        nsource = nsource.rstrip() + source[end:]
    nsource = nsource.strip()

    # Produce output
    out = []
    if warning:
        out.append(r"\kactlwarning{%s: %s}" % (caption, warning))
    if error:
        out.append(r"\kactlerror{%s: %s}" % (caption, error))
    else:
        caption = pathescape(caption).strip()
        out.append(r"\kactlref{%s}" % caption)

        # Make a SHA1-hash of the source code and add a newline before hashing this.
        # Then, take the hexadecimal-version, and turn this into a string.
        sha1_hash = hashlib.sha1(nsource + "\n").hexdigest()

        with open('hashcheck', 'a') as f:
            f.write(nsource + "\n")
            f.write("HASH: " + sha1_hash)
        with open('header.tmp', 'a') as f:
            f.write(caption + "\n")
        if commands.get("Description"):
            out.append(r"\defdescription{%s}" % escape(commands["Description"]))
        if commands.get("Usage"):
            out.append(r"\defusage{%s}" % codeescape(commands["Usage"]))
        if commands.get("Time"):
            out.append(r"\deftime{%s}" % ordoescape(commands["Time"]))
        if commands.get("Memory"):
            out.append(r"\defmemory{%s}" % ordoescape(commands["Memory"]))
        if includelist:
            out.append(r"\leftcaption{%s}" % pathescape(", ".join(includelist)))
        if nsource:
            out.append(r"\rightcaption{SHA1: \texttt{%s}, %d lines}" % (sha1_hash, len(nsource.split("\n"))))
        out.append("\makecaption{%s}\n\\begin{%scode}" % (caption, lang))
        out.append(nsource)
        out.append(r"\end{%scode}" % lang)

    for line in out:
        print(line, file=outstream)

def processraw(caption, instream, outstream, lang = 'raw'):
    try:
        source = instream.read().strip()
        caption = pathescape(caption).strip()
        print(r"\kactlref{%s}" % caption, file=outstream)
        with open('header.tmp', 'a') as f:
            f.write(caption + "\n")
        print(r"\rightcaption{%d lines}" % len(source.split("\n")), file=outstream)
        if lang == 'raw':
            # not used anymore, if I'm not mistaken...
            print(r"\begin{lstlisting}[language=raw,caption={%s}]" % pathescape(caption), file=outstream)
            print(source, file=outstream)
            print(r"\end{lstlisting}", file=outstream)
        else:
            env = lang + 'code'
            print("\makecaption{%s}\n\\begin{%s}" % (caption, env), file=outstream)
            print(source, file=outstream)
            print(r"\end{%s}" % env, file=outstream)
    except:
        print("\kactlerror{Could not read source.}", file=outstream)

def isinclude(line):
    line = line.strip()
    if line.startswith("#include") and not line.endswith("/** keep-include */"):
        return line[8:].strip()
    return None

def getlang(input):
    return input.rsplit('.',1)[-1]

def getfilename(input):
    return input.rsplit('/',1)[-1]

def print_header(data, outstream):
    parts = data.split('|')
    until = parts[0].strip() or parts[1].strip()
    if not until:
        # Nothing on this page, skip it.
        return
    with open('header.tmp') as f:
        lines = [x.strip() for x in f.readlines()]
    if until not in lines:
        # Nothing new on the page.
        return

    ind = lines.index(until) + 1
    def adjust(name):
        return name if name.startswith('.') else name.split('.')[0]
    output = r"\enspace{}".join(map(adjust, lines[:ind]))
    print(output, file=outstream)
    with open('header.tmp', 'w') as f:
        for line in lines[ind:]:
            f.write(line + "\n")

def main():
    language = None
    caption = None
    instream = sys.stdin
    outstream = sys.stdout
    print_header_value = None
    try:
        opts, args = getopt.getopt(sys.argv[1:], "ho:i:l:c:", ["help", "output=", "input=", "language=", "caption=", "print-header="])
        for option, value in opts:
            if option in ("-h", "--help"):
                print("This is the help section for this program")
                print()
                print("Available commands are:")
                print("\t -o --output")
                print("\t -h --help")
                print("\t -i --input")
                print("\t -l --language")
                print("\t --print-header")
                return
            if option in ("-o", "--output"):
                outstream = open(value, "w")
            if option in ("-i", "--input"):
                instream = open(value)
                if language == None:
                    language = getlang(value)
                if caption == None:
                    caption = getfilename(value)
            if option in ("-l", "--language"):
                language = value
            if option in ("-c", "--caption"):
                caption = value
            if option == "--print-header":
                print_header_value = value
        if print_header_value is not None:
            print_header(print_header_value, outstream)
            return
        print(" * \x1b[1m{}\x1b[0m\n".format(caption))

        aliases = {
            'cpp': 'cpp', 'cc': 'cpp', 'c': 'cpp', 'h': 'cpp', 'hpp': 'cpp',
            'java': 'java',
            'bash': 'bash', 'sh': 'bash',
            'python': 'python', 'py': 'python',
            'vim': 'vim',
        }

        if language.startswith('raw'):
            language = language[3:]
            if not aliases.get(language):
                raise ValueError("Unknown language: " + str(language))
            language = aliases.get(language)
            processraw(caption, instream, outstream, language)
        else:
            if not aliases.get(language):
                raise ValueError("Unknown language: " + str(language))
            language = aliases.get(language)
            processwithcomments(caption, instream, outstream, language)
    except (ValueError, getopt.GetoptError, IOError) as err:
        print(str(err), file=sys.stderr)
        print("\t for help use --help", file=sys.stderr)
        return 2

if __name__ == "__main__":
    exit(main())
