# LFI-scan
Local file inclusion (LFI) detection tool made in c++.

## Dependencies
`sudo apt-get install libcurl4-openssl-dev`

## Installation
`git clone git@github.com:skeppis/LFI-scan.git`

## Building
`cd LFI-scan` \
`make`

## Usage
`./LFI-scan -u http://www.example.com/ -w /path/to/wordlist`
