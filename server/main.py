from fastapi import FastAPI, HTTPException, status, Request, Response, UploadFile
from fastapi.responses import StreamingResponse
import structures as structs
import functools
import backend
import json

app = FastAPI()

if __name__ == '__main__':
	import uvicorn
	uvicorn.run('main:app', reload = True)

def exceptionAs422Details(func):
	@functools.wraps(func)
	async def exceptionAs422DetailsDecorator(*args, **kwargs):
		try:
			return await func(*args, **kwargs)
		except Exception as e:
			raise HTTPException(status_code = status.HTTP_422_UNPROCESSABLE_ENTITY, detail=str(e))
	return exceptionAs422DetailsDecorator

@app.get('/')
async def root():
	return {'message' : 'Hello world!'}

@app.get('/info/{path:path}')
@exceptionAs422Details
async def info(path: str):
	return json.loads(backend.info(path))

@app.get('/tree/{path:path}')
@exceptionAs422Details
async def tree(path: str):
	return json.loads(backend.list(path))

@app.get('/tree/')
@exceptionAs422Details
async def tree():
	return tree("")

@app.post('/search/{path:path}')
@exceptionAs422Details
async def search(path: str, phrase: str):
	return json.loads(backend.search(path, phrase))

@app.post('/search/')
@exceptionAs422Details
async def search(phrase: str):
	return search("", phrase)

@app.post('/create/{path:path}')
@exceptionAs422Details
async def create(path: str, entry: structs.FileInfo):
	print(f"Endpoint create, args: {path}, {entry.json()}")
	backend.create(path, entry.name, entry.meta.json())

@app.post('/create/')
@exceptionAs422Details
async def create(entry: structs.FileInfo):
	return create("", entry)

@app.post('/rename/{path:path}')
@exceptionAs422Details
async def rename(path: str, to: str):
	backend.rename(path, to)

@app.post('/move/{path:path}')
@exceptionAs422Details
async def move(path: str, to: str):
	backend.move(path, to)

@app.delete('/delete/{path:path}')
@exceptionAs422Details
async def delete(path: str):
	backend.remove(path)


@app.post('/init-upload/{path:path}')
@exceptionAs422Details
async def initUpload(path: str | None, file: structs.FileInfo, request: Request, response: Response):
	# get the upload id
	upload_id = backend.initializeFileTransfer(path, file.name, file.size, file.meta.json())
	# append upload_id as a query param to the request url
	location_url = str(request.base_url) + "upload/" + str(upload_id)
	response.headers["Location"] = location_url

@app.post('/init-upload/')
@exceptionAs422Details
async def initUpload(file: structs.FileInfo, request: Request, response: Response):
	return initUpload("", file, request, response)

@app.put('/upload/{id}')
@exceptionAs422Details
async def upload(file: UploadFile, id: int):
	chunk_size = 256 * 1024
	bytes_sent = 0
	while(bytes_sent < file.size):
		data_remaining = file.size - bytes_sent
		data: bytes = None
		data_size: int = None
		if(data_remaining > chunk_size):
			data = file.file.read(chunk_size)
			data_size = chunk_size
		else:
			data = file.file.read(data_remaining)
			data_size = data_remaining
		backend.upload(id,
		 bytes_sent,
		 bytes_sent + data_size - 1,
		 data)
		bytes_sent += data_size

@app.get('/download/{path:path}')
@exceptionAs422Details
async def download(path: str) -> bytes:
	chunk_size = 256 * 1024
	file = json.loads(backend.info(path))
	if(file['type'] != 'file'):
		raise Exception('NotAFile')
	filesize = int(file['size'])

	def file_streamer():
		for i in range(chunk_size, filesize, chunk_size):
			yield backend.read(path, i-chunk_size, i - 1)
		remaining_bytes = filesize % chunk_size
		if(remaining_bytes != 0):
			startbyte = filesize - remaining_bytes
			yield backend.read(path, startbyte)
	
	return StreamingResponse(file_streamer())

