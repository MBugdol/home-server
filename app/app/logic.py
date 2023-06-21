import requests
import app.flow as flow
from PySide6.QtCore import QObject, Slot, Signal
from pathlib import PurePath

_default_url = 'http://localhost:8000'

class APICaller(QObject):
	def __init__(self):
		QObject.__init__(self)
		
	@Slot(str, result = "QVariantList")
	def getFiles(self, directory):
		full_path = _default_url + '/tree/' + directory
		response = requests.get(full_path)
		return response.json()
	
	@Slot(str, str, result = "QVariantList")
	def getSearchResults(self, directory, phrase):
		full_path = _default_url + '/search/' + directory
		response = requests.post(full_path, params={"phrase":phrase})
		return response.json()
	
class Backend(QObject):
	cwdChanged = Signal()

	def __init__(self):
		QObject.__init__(self)
		self.ApiCaller = APICaller()
		self.FlowController = flow.FlowController()
		self.cwd = PurePath()
	
	@Slot(result = 'QVariantList')
	def getCurrentChildren(self):
		response = self.ApiCaller.getFiles(str(self.cwd))
		children = response['children']
		return children
	
	@Slot(result = str)
	def getCwd(self):
		return str(self.cwd)
	
	@Slot(str)
	def cd(self, folder):
		self.cwd = self.cwd / folder
		self.cwdChanged.emit()

	@Slot()
	def cdUp(self):
		self.cwd = self.cwd.parent
		self.cwdChanged.emit()

	@Slot(str, str)
	def setCwd(self, path: str, type: str):
		if(type == "directory"):
			self.cwd = path
		else:
			self.cwd = PurePath(path).parent
		self.cwdChanged.emit()

	@Slot(str)
	def searchFor(self, phrase: str):
		response = self.ApiCaller.getSearchResults(str(self.cwd), phrase)
		entries_found = response['matches']
		self.FlowController.push('qrc:/menu/search_results.qml', args={"phrase":phrase, "matches":entries_found})
		return entries_found