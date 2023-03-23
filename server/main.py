from fastapi import FastAPI, HTTPException, status
from structures import TestFileRequest, Folder

from backend import FileHandler

if __name__ == '__main__':
	import uvicorn
	uvicorn.run('main:app', reload = True)
	
app = FastAPI()

fh = FileHandler()
fh.createHomeServerDirectory()

@app.get("/")
def root():
	return {"Hello":"World"}

@app.post("/test/")
def test(param: TestFileRequest):
	result =  f'Test request of file {param.filename}, which ' + ('is' if param.isFolder else 'isn\'t') + f' a folder'
	if(param.testParam is not None):
		result += f' with a test param of {param.testParam}'
	result += '.'
	return result

@app.post("/add-folder/")
def add_folder(folder: Folder):
	try:
		fh.createFolder(folder.directory)
	except:
		raise HTTPException(status_code = status.HTTP_422_UNPROCESSABLE_ENTITY, detail="The given folder path must be absolute with regard to server root directory")