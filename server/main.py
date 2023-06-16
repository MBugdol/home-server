from fastapi import FastAPI, HTTPException, status, Request, Response, UploadFile
import structures as structs
import functools
import backend

app = FastAPI()

if __name__ == '__main__':
	import uvicorn
	uvicorn.run('main:app', reload = True)

def exceptionAs422Details(func):
	@functools.wraps(func)
	def exceptionAs422DetailsDecorator(*args, **kwargs):
		try:
			return func(*args, **kwargs)
		except Exception as e:
			raise HTTPException(status_code = status.HTTP_422_UNPROCESSABLE_ENTITY, detail=str(e))
	return exceptionAs422DetailsDecorator

@app.get('/')
def root():
	return {'message' : 'Hello world!'}


@app.put('/upload/{id}')
@exceptionAs422Details
def upload(file: UploadFile, id: int):
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

@app.post('/init-upload/{path:path}')
@exceptionAs422Details
def initUpload(path: str | None, file: structs.FileInfo, request: Request, response: Response):
	# get the upload id
	upload_id = backend.initializeFileTransfer(path, file.name, file.size, file.meta.json())
	# append upload_id as a query param to the request url
	location_url = str(request.base_url) + "/upload/" + str(upload_id)
	response.headers["Location"] = location_url

@app.post('/init-upload/')
@exceptionAs422Details
def initUpload(file: structs.FileInfo, request: Request, response: Response):
	return initUpload("", file, request, response)

@app.post('/create/{path:path}')
@exceptionAs422Details
def create(path: str, entry: structs.FileInfo):
	print(f"Endpoint create, args: {path}, {entry.json()}")
	backend.create(path, entry.name, entry.meta.json())

@app.post('/create/')
@exceptionAs422Details
def create(entry: structs.FileInfo):
	return create("", entry)
