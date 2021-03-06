# Islandora Orphaned Objects [![Build Status](https://travis-ci.org/bondjimbond/islandora_orphaned_objects.png?branch=7.x)](https://travis-ci.org/bondjimbond/islandora_orphaned_objects)

## Deprecation notice

As of March 22, 2018 (if running on HEAD) or the Islandora 7.x-1.11 release, the Orphaned Objects functionality has been merged into the core Islandora module. In these versions of Islandora, the Orphaned Objects list will be available via the admin menu under Reports -> Orphaned Islandora Objects.

If you have been using Islandora Orphaned Objects and are using or preparing to use the latest Islandora code, please uninstall Islandora Orphaned Objects to avoid conflicts.

If you are not upgrading to the latest Islandora version, this module will remain available. I will be maintaining the module and responding to issues for the foreseeable future.

## Introduction

When a parent object is deleted via its parent's context, its child objects are not removed. These objects become orphaned, their RELS-EXT proclaiming a relationship with a parent that no longer exists. These objects become lost in the repository, taking up space and occasionally turning up unexpectedly in search results.

Islandora Orphaned Objects finds these orphans, creates a list, and provides the option to purge them. Works with the following types of orphaned object:

* Standard objects with the isMemberOfCollection relationship
* Paged content objects with the isMemberOf relationship (including Newspaper Issues, Newspaper Pages, and Book Pages)

## Requirements

This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

Orphaned Objects can be viewed at Administration » Islandora » Islandora utility modules » Orphaned objects (admin/islandora/tools/orphaned_objects/list).

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
