import requests
import app.flow as flow
from PySide6.QtCore import QObject, Slot, Signal, QUrl, QFileInfo
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
	
	@Slot(str, str)
	def create(self, directory, type):
		full_path = _default_url + '/create/' + directory
		body = {
			'name': 'NewFolder',
			'meta': {
				'type': type
			}
		}
		response = requests.post(full_path, json = body)

	@Slot(str, str, int, 'QVariantList', result=str)
	def initUpload(self, directory, name, size, metadata):
		full_path = _default_url + '/init-upload/' + directory
		body = {
			'name': name,
			'size': size,
			'meta': metadata
		}
		response = requests.post(full_path, json=body)
		return response.headers["Location"]

	@Slot("QVariantList", str)
	def upload(self, files, location):
		response = requests.put(location, files=files)
	
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
			self.cwd = PurePath(path)
		else:
			self.cwd = PurePath(path).parent
		self.cwdChanged.emit()

	@Slot(str)
	def searchFor(self, phrase: str):
		response = self.ApiCaller.getSearchResults(str(self.cwd), phrase)
		entries_found = response['matches']
		self.FlowController.push('qrc:/menu/search_results.qml', args={"phrase":phrase, "matches":entries_found})
		return entries_found
		
	# Creation

	@Slot()
	def createNewFolder(self):
		self.ApiCaller.create(str(self.cwd), 'application/x-directory')
		self.cwdChanged.emit()

	@Slot(str)
	def uploadFile(self, path):
		path_url = QUrl(path)
		file_info = QFileInfo(path_url.toLocalFile())
		upload_location = self.ApiCaller.initUpload(str(self.cwd), 
				path_url.fileName(), 
				file_info.size(),
				{})
		file = {'file': open(path_url.toLocalFile(), 'rb')}
		self.ApiCaller.upload(file, upload_location)
		self.cwdChanged.emit()