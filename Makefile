.PHONY: necdos

necdos: platform/necdos/gdc16.c platform/necdos/mouse.c src/draw.c src/res.c src/stage.c src/main.c
	lcc platform\necdos\gdc16.c platform\necdos\mouse.c src\draw.c src\res.c src\stage.c src\main.c -o asdf.exe
