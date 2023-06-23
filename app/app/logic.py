import requests
import app.flow as flow
from PySide6.QtCore import QObject, Slot, Signal, QUrl, QFileInfo
from pathlib import PurePath
import functools

_default_url = 'http://localhost:8000'

class APICaller(QObject):
	def __init__(self):
		QObject.__init__(self)

	def throwExceptionAt4XX(func):
		@functools.wraps(func)
		def throwExceptionAt4XXDecorator(*args, **kwargs):
			response = func(*args, **kwargs)
			if(response.status_code >= 400):
				raise Exception(response.json()["detail"])
			return response
		return throwExceptionAt4XXDecorator
	
	@throwExceptionAt4XX
	def get(self, *args, **kwargs):
		return requests.get(*args, **kwargs)

	@throwExceptionAt4XX
	def put(self, *args, **kwargs):
		return requests.put(*args, **kwargs)

	@throwExceptionAt4XX
	def post(self, *args, **kwargs):
		return requests.post(*args, **kwargs)
	
	@throwExceptionAt4XX
	def delete(self, *args, **kwargs):
		return requests.delete(*args, **kwargs)

	@Slot(str, result = "QVariantList")
	def getFiles(self, directory):
		full_path = _default_url + '/tree/' + directory
		response = self.get(full_path)
		return response.json()
	
	@Slot(str, str, result = "QVariantList")
	def getSearchResults(self, directory, phrase):
		full_path = _default_url + '/search/' + directory
		response = self.post(full_path, params={"phrase":phrase})
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
		response = self.post(full_path, json = body)

	@Slot(str, str, int, 'QVariantList', result=str)
	def initUpload(self, directory, name, size, metadata):
		full_path = _default_url + '/init-upload/' + directory
		body = {
			'name': name,
			'size': size,
			'meta': metadata
		}
		response = self.post(full_path, json=body)
		return response.headers["Location"]

	@Slot("QVariantList", str)
	def upload(self, files, location):
		response = self.put(location, files=files)

	def download(self, directory):
		full_path = _default_url + '/download/' + directory
		response = self.get(full_path)
		return response
	
	def remove(self, directory):
		full_path = _default_url + '/delete/' + directory
		self.delete(full_path)

	def rename(self, directory, new_name):
		full_path = _default_url + '/rename/' + directory
		self.post(full_path, params = {'to': new_name})

	def move(self, directory, new_location):
		full_path = _default_url + '/move/' + directory
		self.post(full_path, params = {'to': new_location})
	
class Backend(QObject):
	cwdChanged = Signal()
	errorOccured = Signal(str)

	def __init__(self):
		QObject.__init__(self)
		self.ApiCaller = APICaller()
		self.FlowController = flow.FlowController()
		self.cwd = PurePath()
		self.MoveOrigin = ''

	def raiseErrorOnException(func):
		@functools.wraps(func)
		def raiseErrorOnExceptionDecorator(self, *args, **kwargs):
			try:
				return func(self, *args, **kwargs)
			except Exception as e:
				self.errorOccured.emit(str(e))
		return raiseErrorOnExceptionDecorator
	
	@Slot(result = 'QVariantList')
	@raiseErrorOnException
	def getCurrentChildren(self):
		response = self.ApiCaller.getFiles(str(self.cwd))
		children = response['children']
		return children
	
	@Slot(result = str)
	@raiseErrorOnException
	def getCwd(self):
		return str(self.cwd)
	
	@Slot(str)
	@raiseErrorOnException
	def cd(self, folder):
		self.cwd = self.cwd / folder
		self.cwdChanged.emit()

	@Slot()
	@raiseErrorOnException
	def cdUp(self):
		self.cwd = self.cwd.parent
		self.cwdChanged.emit()

	@Slot(str, str)
	@raiseErrorOnException
	def setCwd(self, path: str, type: str):
		if(type == "directory"):
			self.cwd = PurePath(path)
		else:
			self.cwd = PurePath(path).parent
		self.cwdChanged.emit()

	@Slot(str)
	@raiseErrorOnException
	def searchFor(self, phrase: str):
		response = self.ApiCaller.getSearchResults(str(self.cwd), phrase)
		entries_found = response['matches']
		self.FlowController.push('qrc:/menu/search_results.qml', args={"phrase":phrase, "matches":entries_found})
		return entries_found
		
	# Creation

	@Slot()
	@raiseErrorOnException
	def createNewFolder(self):
		self.ApiCaller.create(str(self.cwd), 'application/x-directory')
		self.cwdChanged.emit()

	@Slot(str, str)
	@raiseErrorOnException
	def rename(self, entry, new_name):
		full_path = self.cwd / entry
		self.ApiCaller.rename(str(full_path), new_name) 
		self.cwdChanged.emit()

	@Slot(str)
	@raiseErrorOnException
	def delete(self, entry):
		full_path = self.cwd / entry
		self.ApiCaller.remove(str(full_path))
		self.cwdChanged.emit()

	@Slot(str)
	@raiseErrorOnException
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

	@Slot(str, str)
	@raiseErrorOnException
	def downloadFile(self, file, local_path):
		full_path = self.cwd / file
		streamer = self.ApiCaller.download(str(full_path))
		with open(QUrl(local_path).toLocalFile(), 'wb') as out:
			for chunk in streamer.iter_content(1024 * 256):
				out.write(chunk)

	@Slot(str)
	@raiseErrorOnException
	def move(self, file):
		self.MoveOrigin = self.cwd / file

	@Slot(result = str)
	@raiseErrorOnException
	def getMoveOrigin(self):
		return str(self.MoveOrigin)
	
	@Slot()
	@raiseErrorOnException
	def paste(self):
		target_path = self.cwd / self.MoveOrigin.name
		self.ApiCaller.move(str(self.MoveOrigin), str(target_path))
		self.MoveOrigin = ''
		self.cwdChanged.emit()
