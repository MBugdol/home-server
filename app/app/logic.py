import requests
import json
from PySide6.QtCore import QObject, Slot, Signal
from pathlib import PurePath

_default_url = 'http://localhost:8000'

class APICaller(QObject):
	def __init__(self):
		QObject.__init__(self)
		
	@Slot(str, result = bool)
	def getFiles(self, directory):
		full_path = _default_url + '/tree/' + directory
		response = requests.get(full_path)
		return response.json()
	
class Backend(QObject):
	cwdChanged = Signal()

	def __init__(self):
		QObject.__init__(self)
		self.ApiCaller = APICaller()
		self.cwd = PurePath()
	
	@Slot(result = "QVariantList")
	def getCurrentChildren(self):
		response = self.ApiCaller.getFiles(str(self.cwd))
		children = response["children"]
		return children
	
	@Slot(str)
	def cd(self, folder):
		self.cwd = self.cwd / folder
		self.cwdChanged.emit()