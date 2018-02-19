CC = lcc
LD = lld

!include mk/$(PLATFORM).mk
#!include mk/$(CC).mk
!include mk/common.mk
OFILES = $(PLATFORM_OFILES) $(OFILES)

.c.$O:
	$(CC) $(CFLAGS) -c $<

$(TARG)$(EXE): $(OFILES)
	$(CC) -o $@ $(CFLAGS) $(OFILES)
