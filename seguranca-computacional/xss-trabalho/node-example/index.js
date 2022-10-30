const express = require('express');
var qs = require('querystring');
var url = require('url');
var fs = require('fs');

const app = express();

const APP_PORT = 3000;

app.get("/", (req, res) => {
  console.log("req.url -> ", req.url);
  let query = qs.parse(url.parse(req.url).query)
  console.log("query -> ", query);
  console.log("query.xss -> ", query.xss);
  console.log("query.xss -> ", query.xss);
  let headers = {
    'X-XSS-Protection': 0
  }

  if (query.xss === "on") {
    headers['X-XSS-Protection'] = 1
  }

  if (query.xss === "off") {
    delete headers['X-XSS-Protection'];
  }

  if (query.csp === 'on') {
    headers['Content-Security-Policy'] = `default-src 'self'`
  }

  if (query.csp === 'report') {
    headers['Content-Security-Policy-Report-Only'] = `default-src 'self'`
  }

  res.writeHead(200, headers)
  let keyword = query.search || ''
  let results = keyword ? `You searched for "${keyword}", we found:</br><img src="http://placekitten.com/200/300" />` : `Try searching...`

  res.end(fs.readFileSync(__dirname + '/index.html').toString().replace('__KEYWORD__', keyword).replace('__RESULTS__', results))

});

app.listen(APP_PORT, () => console.log(`server listening on port ${APP_PORT}`));
