## Add

import uiScriptlocale

## AFTER

ROOT = "d:/ymir work/ui/minimap/"

## Add

ASSETS = "Assets/ui/minimap/{}"
Main_ButtonGroupCounter = 0
def Main_GetButtonGroup(inc = False):
	global Main_ButtonGroupCounter

	if inc:
		Main_ButtonGroupCounter += 1
	return Main_ButtonGroupCounter

def BuildLabel(type, text, ico, lPos = (0, 0)):
	return {
		"name" : "Label_" + type,
		"type" : "image",

		"x" : -lPos[0], "y" : lPos[1],
		"image" : ASSETS.format("bg_{}.png".format(ico)),
		"children" :
		[
			## Append Icon
			{
				"name" : "MaskIco_" + type,
				"type" : "image",

				"x" : -10, "y" : 0,
				"vertical_align" : "center",
				"image" : ASSETS.format("mask_.png"),
				"children" :
				[
					{
						"name" : "Ico_" + type,
						"type" : "image",

						"x" : 0, "y" : 0,
						"horizontal_align" : "center",
						"vertical_align" : "center",
						"image" : ASSETS.format("{}_ico.png".format(ico)),
					},
				],
			},

			## Register Wrapper Content
			{
				"name" : "LabelWrapper_" + type,

				"x" : 22, "y" : 3,
				"width" : lPos[0] - 20, "height" : 22,
				"children" :
				[
					{
						"name" : "LabelContent_" + type,
						"type" : "text",

						"x" : 0, "y" : -3,
						"horizontal_align" : "center",
						"vertical_align" : "center",
						"text_horizontal_align" : "center",
						"text_vertical_align" : "center",
						"text" : text,
					},
				],
			},
		],
	}


## After

window = {
	"name" : "MiniMap",
	"style" : ("float", "animate",),

	"x" : SCREEN_WIDTH - 136,
	"y" : 0,

	"width" : 136,
	"height" : 137,

	"children" :
	(
		
## Add

		BuildLabel("NAME", "-", "map", (132, 20)),
		BuildLabel("BOSS", "0", "boss", (70, 20 + 35)),
		BuildLabel("STONES", "0", "stones", (70, 20 + 35 * 2)),
