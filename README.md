# MailBoxDB
> Copyright (c) 2025 Cosmin Cioranu, cosmin@nbeta.ro
> see README.dbmail.md

## What is it?

MailBoxDB is a collection of programs that enables email to be managed, stored in
MailBoxDB is drop in replacement of DBMail

## Why is it useful?

- Securely and scaleably manages user emails with industry standard IMAP;

- Integrates with existing authentication backends including ActiveDirectory
and OpenLDAP;

- MailBoxDB is scalable including multiple terrabyte installations;

- MailBoxDB is flexible. You can run dbmail programs on different servers talking
  to the same database;

- Email filtering is integrated into MailBoxDB and managed using SIEVE;

- Schema upgrades are automatic with SQL provided for DBAs who wish to upgrade
  manually;

- Easy to use and flexible logging for each service;

- An experimental Docker image is available;

- High Availability thanks to database replication and Docker images;

- Data safety thanks to database replication;

- Secure connections thanks to TLS;

- MailBoxDB is database driven so no need of systemusers;

- No need to maintain system users or write access to the filesystem;

- MailBoxDB is Free with a recognised GPL2 Open Source licence.

## Who created it?

MailBoxDB is based on DBMail which was originally created by IC&S in the Netherlands.

MailBoxDB was created by Cosmin Cioranu buiding on top of the original DBMail. 

Around 2025, Cosmin Cioranu has taken the decision to create a deep fork of DBMail in 
order to add new features that were not possible to be integrated to DBMail due to directional
disagreements with DBMail team. 

Also as DBMail, MailBoxDB is now a community effort to create a fast, effecient and scalable
database driven mailingsystem, Therefore MailBoxDB has the GPL licence.

## Support

Support is available by raising an issue at https://github.com/nbeta-ware/mailboxdb

### Architecture

For an architectural overview of DBMail and its components please visit:
https://dbmail.org/architecture/

## Future

Check the https://github.com/nbeta-ware/mailboxdb for further MailBoxDB plans.

## What kind of licence is MailBoxDB?

MailBoxDB uses the GPL version 2 licence. 

It's included in the COPYING file.

## How do I install it?

MailBoxDB is available on many Linux and BSD distributions.

There is also an experimental
[Docker image](https://hub.docker.com/r/alanhicks/dbmail)
with instructions to configure compose.yaml at
https://dbmail.org/docker/

## Installation Procedure

Check README and INSTALL files and on https://dbmail.org for detailed
information and HOWTOs including how to use the Docker image.

See also contrib, debian and docker on https://github.com/dbmail/dbmail

### Configuration

There are various settings including database access, authentication and
logging. Please see dbmail.conf or https://dbmail.org/man-pages/dbmailconf/

Exim is a modern MTA and there is an example configure at
https://github.com/dbmail/dbmail/blob/main/contrib/exim-dbmail-configure

### Integration

MailBoxDB integrates with most MTAs. There are a number of examples on
https://dbmail.org/docs/

Web frontends including [SquirrelMail](https://squirrelmail.org/) and
[Roundcube](https://roundcube.net/) work well with IMAP using dbmail-imapd
plus Roundcube and most desktop software has integration with email filtering
via dbmail-sieved.

### Dependencies

* Database: Current versions of MySQL, PostgreSQL, Sqlite3 and Oracle
* Glib: (>= 2.16)
* GMime: (>= 3 (3.2))
* OpenSSL
* libmhash
* libzdb (http://www.tildeslash.com/libzdb/)
* libevent: (>= 2.1)
* Optional: libsieve (>= 2.2.1) (https://github.com/sodabrew/libsieve)
* Optional: jemalloc

### Installing

* Download MailBoxDB package
* Install dependencies (some provided from your linux / BSD distribution and
  some (libzdb and/or libsieve) need to be compiled
* ./configure
* make 
* make install
