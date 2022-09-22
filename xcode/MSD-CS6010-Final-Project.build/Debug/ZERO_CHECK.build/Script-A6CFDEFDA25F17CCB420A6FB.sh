#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/howard/MSD-CS6010-Final-Project/xcode
  make -f /Users/howard/MSD-CS6010-Final-Project/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/howard/MSD-CS6010-Final-Project/xcode
  make -f /Users/howard/MSD-CS6010-Final-Project/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/howard/MSD-CS6010-Final-Project/xcode
  make -f /Users/howard/MSD-CS6010-Final-Project/xcode/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/howard/MSD-CS6010-Final-Project/xcode
  make -f /Users/howard/MSD-CS6010-Final-Project/xcode/CMakeScripts/ReRunCMake.make
fi

