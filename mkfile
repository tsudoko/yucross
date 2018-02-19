</sys/src/ape/config
<mk/common.mk
OFILES=$OFILES platform/plan9/platform.$O

default:V: $TARG
all:V: $TARG

%.$O: %.c
	$CC $CFLAGS -co $target $prereq

$TARG: $OFILES $LIB
	$LD $LDFLAGS -o $target $prereq
