</sys/src/ape/config
<mk/common.mk
OFILES=$OFILES platform/plan9/platform.$O

default:V: $TARG
all:V: $TARG

$O.out: $OFILES $LIB
	$LD $LDFLAGS -o $target $prereq

%.$O: %.c
	$CC $CFLAGS -co $target $prereq

$TARG: $O.out
	cp $O.out $TARG
