def getLocaleMapName(key):
	return {
		1   :   METIN2_MAP_A1,
	}.get(key, "Error")

def Get(name):
	return globals().get(name, str(name))
