from fastapi import FastAPI, HTTPException, status
from structures import Folder

from backend import FileHandler

if __name__ == '__main__':
	import uvicorn
	uvicorn.run('main:app', reload = True)
	
app = FastAPI()

fh = FileHandler()

@app.get('/')
def root():
	return {'message' : 'Hello world!'}

@app.post('/add-folder/')
def add_folder(folder: Folder):
	try:
		fh.createFolder(folder.directory)
	except Exception as e:
		print(e)
		raise HTTPException(status_code = status.HTTP_422_UNPROCESSABLE_ENTITY, detail='The given folder path must be absolute with regard to server root directory')