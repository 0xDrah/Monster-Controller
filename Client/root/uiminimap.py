## After

			self.serverInfo = self.GetChild("ServerInfo")

## Add

			self._contents = {
				"NAME" : [self.GetChild("Label_NAME"), self.GetChild("LabelContent_NAME")],
				"BOSS" : [self.GetChild("Label_BOSS"), self.GetChild("LabelContent_BOSS")],
				"STONES" : [self.GetChild("Label_STONES"), self.GetChild("LabelContent_STONES")],
			}

## After

	def HideMiniMap(self):
		miniMap.Hide()
		self.OpenWindow.Hide()
		self.CloseWindow.Show()
		
## Add

		for _ in self._contents.values():
			_[0].Hide()
			
## After

	def ShowMiniMap(self):
		if not self.canSeeInfo:
			return

		miniMap.Show()
		self.OpenWindow.Show()
		self.CloseWindow.Hide()
		
## Add

		for _ in self._contents.values():
			_[0].Show()
			
## Add at the end

	def RegisterCounter(self, key, size):
		keysToEnum = ("STONES", "BOSS")
		self._contents[keysToEnum[key]][1].SetText(size)
