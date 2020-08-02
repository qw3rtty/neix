# neix - a news reader for your terminal
**neix** is free software. It is an terminal feed reader for all common RSS/Atom feeds on the web out there.  
It will protect your privacy with a nice looking TUI and with an nice performance.

## :page_facing_up: Table of Contents
- [Installation](#installation)
- [Uninstall](#uninstall)
- [Unit tests](#unit-tests)
- [Usage](#usage)
- [Configuration](#configuration)
- [Contributing](#contributing)
- [Roadmap](#roadmap)
- [Known bugs](#known-bugs)
- [Libaries in usage](#libaries-in-usage)
- [Supported by](#supported-by)
- [License](#license)

## Installation
Follow the steps below for installing:  
```bash
$ git clone https://github.com/tomschwarz/neix.git  
$ cd neix  
$ cmake .  
$ make  
$ sudo make install
```

## Uninstall
Follow the steps below for uninstalling:  
```bash
$ cd neix # should be the same directory where the repository was cloned into  
$ sudo make uninstall
```

If there is an error during the uninstall process or you don't have the directory anymore following the steps below:  
```bash
$ sudo updatedb  
$ locate neix # $ locate neix | grep /usr - if the output is to large  
$ sudo rm {PATH}/neix # where {PATH} is the full path to the binary  
```

## Unit tests
Follow the steps below for unit testing after the installation guide:  
```bas
$ ./bin/tests    
```
Hint: you have to be in the main directory of neix!

## Usage
```bash
$ neix
```

## Configuration
Default path of the config files: **~/.config/neix/**   
There are two configuration files. One for neix itself and one for the feeds.  

## Contributing
If you want to contribute check the [CONTRIBUTING.md](https://github.com/tomschwarz/neix/blob/master/.github/CONTRIBUTING.md)

## Roadmap
* [ ] Add SQLite
* [ ] Add tags to feeds
* [ ] Add rendering for content
* [ ] Add logging

## Known bugs
Currently are no bugs known/reported.  
If you find any bugs, don't hesitate and open an issue :)

## Libaries in usage
- [rapidXML](http://rapidxml.sourceforge.net/) is used for XML parsing

## Supported by  
I can proudly say, that I get support from:  

- JetBrains: CLion open-source license

## License
[GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/) © [Tom Schwarz](https://github.com/tomschwarz)
