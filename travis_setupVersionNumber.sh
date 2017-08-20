#!/bin/sh

echo Setting up version numbers

hhsh=`git log --pretty=format:"%H" | head -1 | cut -c1-8`

echo Got Git revision ${hhsh}

sed -e "s%RS_REVISION_NUMBER.*%RS_REVISION_NUMBER   0x${hhsh}%" ./libretroshare/src/retroshare/rsversion.in > ./libretroshare/src/retroshare/rsversion.h

echo Done.

