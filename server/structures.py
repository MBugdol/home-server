from pydantic import BaseModel

class FileMetaData(BaseModel):
	type: str = 'application/octet-stream'

class FileInfo(BaseModel):
	name: str
	size: int | None
	meta: FileMetaData | None

class TestFileRequest(BaseModel):
	filename: str
	isFolder: bool
	testParam: int | None

class Folder(BaseModel):
	directory: str

class User(BaseModel):
	login: str
	password: str