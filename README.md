# Universal Analytics in C

This library provides a C interface to Google Analytics, supporting the Universal Analytics Measurement Protocol.

**NOTE** this project is reasonably feature-complete for most use-cases, covering all relevant features of the Measurement Protocol, however we still consider it _beta_. Please feel free to file issues for feature requests.

# Contact
Email: `opensource@analyticspros.com`

# Usage

For the most accurate data in your reports, Analytics Pros recommends establishing a distinct ID for each of your users, and integrating that ID on your front-end web tracking, as well as tracking calls from other platforms (where this C library would run). This provides for a consistent, correct representation of user engagement, without skewing overall visit metrics (and others).

Please see the the following examples:

- [test.c](./test.c) for dynamic allocation example
- [test-static.c](./test-static.c) for static allocation example


We'll be building out additional examples of all available tracking within it. Currently it only highlights Pageview and Event tracking, but the remaining types should be fairly intuitive extensions.

Due to the constraints of the C language, this library's interface that differs slightly from Google's `analytics.js` implementation. In particular, `enum` constants are used to specify parameter fields, rather than strings (i.e. by parameter name). This offers some measurable efficiencies, while remaining quite readable (in our opinion).


# Dispatch mechanism

**DRAFT**

- Cap at 500 hits per session; session is app runtime (timestamp at start)
- Replay old sessions by adjusting date
- Session duration build-time option (#define) at 6hours default
- Provide alternate HTTP request callback support

Queueing mechanism:

- Read cache at start
- Write cache at 10 seconds, exit, and flush
	- Truncate data at 2MB; drop older sessions
- Push requests into queue
- When response is 200, remove from queue
- When response is NOT 200, signal wait to pause the queue for 5 minutes
- Provide interface to re-start queue (before 5min retry) - event trigger callback
- Attempt to flush the queue every 5 minutes, regardless of length
- Consider decay method to reduce retry frequency on subsequent failures... 
	- 5m, 5m, 10m, 20m, 30m...
	- Not less frequently than 30 minutes


Transparent queueing and caching; user code shouldn't have to know about it.

# User libraries

Provide interfaces in
- C++ (for statefulness, access layer for other libs)
- C#
- Objective-C


# Features not implemented


# License

universal-analytics-c is licensed under the [BSD license](./LICENSE)

