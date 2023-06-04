from pydantic import BaseModel

class TestFileRequest(BaseModel):
	filename: str
	isFolder: bool
	testParam: int | None

class Folder(BaseModel):
	directory: str

class User(BaseModel):
	login: str
	password: str