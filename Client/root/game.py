## Before

		self.serverCommander=stringCommander.Analyzer()
		for serverCommandItem in serverCommandList.items():
	
## Add

		serverCommandList['MonsterControllerCRegister'] = self.MonsterControllerCRegister_

## At the end of file add

	def MonsterControllerCRegister_(self, key, size):
		if self.interface:
			self.interface.wndMiniMap.RegisterCounter(int(key), size)
