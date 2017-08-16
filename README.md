# Islandora Orphaned Objects [![Build Status](https://travis-ci.org/Islandora/islandora_orphaned_objects.png?branch=7.x)](https://travis-ci.org/bondjimbond/islandora_orphaned_objects)

## Introduction

When a parent collection is deleted, in some cases its child objects are not. These objects become orphaned, their RELS-EXT proclaiming a relationship with a parent that no longer exists. These objects become lost in the repository, taking up space and occasionally turning up unexpectedly in search results.

Islandora Orphaned Objects finds these orphans, creates a list, and provides the option to purge them. Currently restricted to standard objects with an "isMemberOfCollection" relationship. Page objects and other features to be added soon.

## Requirements

This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

Orphaned Objects can be viewed at Administration » Islandora » Simple Workflow objects (admin/islandora/tools/orphaned_objects/list).

## Documentation

Further documentation for this module is available at [our wiki](https://wiki.duraspace.org/display/ISLANDORA/Simple+Workflow).

## Troubleshooting/Issues

Having problems or solved a problem? Check out the Islandora google groups for a solution.

* [Islandora Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora)
* [Islandora Dev Group](https://groups.google.com/forum/?hl=en&fromgroups#!forum/islandora-dev)

## Maintainers/Sponsors

Current maintainers:

* [Brandon Weigel](https://github.com/bondjimbond)

## Development

If you would like to contribute to this module, please check out [CONTRIBUTING.md](CONTRIBUTING.md). In addition, we have helpful [Documentation for Developers](https://github.com/Islandora/islandora/wiki#wiki-documentation-for-developers) info, as well as our [Developers](http://islandora.ca/developers) section on the [Islandora.ca](http://islandora.ca) site.

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
