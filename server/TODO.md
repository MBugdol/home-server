# C++

## Important

- [ ] /download/path endpoint
- [ ] basic user authentication
- [ ] secure query class
- [ ] secure table requests for nonexistent entries
- [ ] bind uploads to users
- [ ] server initializer class

Libs:
- [ ] threads (async in PY)

## Later date
- ### Authentication
	- [ ] one token per IP address
	- [ ] bcrypt for auth
	- [ ] OAuth2
	- [ ] two-factor-auth (physical key, mobile device)
	- [ ] admin only for physical key bearer

- ### Functionality
	- [ ] upload whole folders at once
	- [ ] music streaming
	- [ ] video streaming
	- [ ] text documents streaming

- ### Refactoring
	- [ ] UploadManager as a class template?
	- [ ] sqlite3 query builder (another project; refactor related code when the query builder will have been finished)
	- [ ] add tests
	- [ ] EntryList class

- ### Bachelors expansion
	- [ ] branch off into online music analysis

## Finished

- [x] error when creating the file fails on the system side
- [x] filesystem
- [x] file transfer endpoints:
	- [x] /upload/id/ endpoint
	- [x] UploadManager
	- [x] FileMetadata
- [x] /tree/path/ endpoint
- [x] ranges
- [x] /search/ endpoint
- [x] regex