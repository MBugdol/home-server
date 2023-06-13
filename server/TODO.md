# C++

## Important

- [ ] basic user authentication
- [ ] error when creating the file fails on the system side
- [ ] file transfer endpoints:
	[ ] UploadManager
	[ ] FileMetadata
- [ ] endpoint safety
- [ ] secure query class
- [ ] secure table requests for nonexistent entries
- [ ] jwt validation

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

- ### Bachelors expansion
	- [ ] branch off into online music analysis