# FnordMetric v0.8.0

FnordMetric is a collection of lightweight tools for real-time metrics collection
and visualization with SQL. The tools allow you to record measurements and
build beautiful real-time dashboards within minutes. All using your favorite SQL
database (currently supported are MySQL, Postgres and EventQL).

<ul>
  <li>
    <h4 style="margin-bottom:.2em; font-size:16px;"><a href="/documentation/metric-collectd">metric-collectd</a></h4>
    <p>
      metric-collectd is a lightweight daemon that collects measurements and other
      timeseries data, pre-aggregates it and stores the resulting tuples into a
      backend database. metric-collectd can currently listen for samples in
      Text/StatsD or JSON format via UDP or HTTP. It can also pull samples via
      HTTP or SNMP.
    </p>
  </li>

  <li>
    <h4 style="margin-bottom:.2em; font-size:16px;"><a href="/documentation/metric-queryd">metric-queryd</a></h4>
    <p>
      metric-queryd is a simple HTTP service that executes SQL queries on a backend
      database and plots the results. The HTTP API allows you to create timeseries graphs
      and other visualizations using nothing but SQL. You can easily plug the returned
      charts into a HTML site to create a real-time SQL-powered dashboard.
    </p>
  </li>
</ul>

The two services, `metricd-collectd` and `metric-queryd` do not depend on each
other and don't share a lot of code. If you're only interested in the data capture
part or only in the visualization part, you can run only one of the services.

To get started with FnordMetric, have a look at these pages:
[Getting Started](/documentation/getting-started),
[Data Model](/documentation/data-model)

<div class="notice">
  <div style="float:right;"><a class="github-button" data-style="mega" href="https://github.com/paulasmuth/fnordmetric" data-count-href="/paulasmuth/fnordmetric/stargazers" data-count-api="/repos/paulasmuth/fnordmetric#stargazers_count" data-count-aria-label="# stargazers on GitHub" aria-label="Star paulasmuth/fnordmetric on GitHub">View on GitHub</a></div>
  Join FnordMetric development now on GitHub. We're always appreciating new pull requests, bugs and feature requests!
</div>


## Web Interface

Optionally, `metric-queryd` can expose a web interface that allows you to execute
SQL queries and create charts:

<div style="width:820px;margin:1em auto 3em auto;height: 495px;overflow: hidden;border: 1px solid #ccc;border-radius: 3px;box-shadow: 1px 2px 6px rgba(0,0,0,.1);" class="shadow">
  <video width="820" autoplay="autoplay" loop>
    <source src="/fnordmetric-server.mp4" type="video/mp4">
    <script type="text/javascript">
      if (!(navigator.userAgent.search("Safari") >= 0 && navigator.userAgent.search("Chrome") < 0)) {
        document.write('<source src="/fnordmetric-server.webm" type="video/webm">');
      }
    </script>
    <img src="/img/fnordmetric_server_screen.png" width="875" />
  </video>
</div>


## Examples

Here are some example charts that were generated using `metric-queryd` and SQL to
give you some ideas on what is possible. Have a look at the
[full list of examples](/examples/) for more.

<div style="height: .6em;"></div>

_Example: Simple timeseries chart_
<a href="/examples/linecharts/simple_lines"><img src="/examples/linecharts/simple_lines/simple_lines.png" style="width: 100%;" /></a>

_Example: Chart with explicit domain and legend_
<a href="/examples/linecharts/explicit_domain"><img src="/examples/linecharts/explicit_domain/explicit_domain.png" style="width: 100%;" /></a>

_Example: Horizontal barchart_
<a href="/examples/barcharts/horizontal_bars"><img src="/examples/barcharts/horizontal_bars/horizontal_bars.png" style="width: 100%;" /></a>

_Example: Scatter chart with lables_
<a href="/examples/pointcharts/pointchart_with_labels"><img src="/examples/pointcharts/pointchart_with_labels/pointchart_with_labels.png" style="width: 100%;" /></a>


## Supported Databases

These currently supported databases are [MySQL](/documentation/backend-mysql), 
[Postgres](/documentation/backend-postgres) and [EventQL](/documentation/backend-eventql).
If you'd like to add a new backend, please have a look at `src/fnordmetric/backends` and
create a pull request on GitHub.

### Why FnordMetric?

One way to look at FnordMetric is that it's a SQL-based alternative to the
StatsD/Graphite, ELK or Prometheus stacks. So why would you choose FnordMetric
over these other solutions? Here are some reasons:

- The FnordMetric programs are just simple, stateless middleware services. All
  the heavy lifting is done by the backend database. You get to use the full
  power of a true RDBMS for your timeseries collection and querying.

- In the same vein, you don't have to learn another informally specified domain
  specific query language for your metrics/graphing tool. It's just SQL

- Also consider that since all your metrics data will be stored in a SQL database,
  you can easily JOIN it with other (non-timeseries) data tables, for example
  with records from your main production database.

- FnordMetric follows the unix philosophy: Do one thing and do it well. FnordMetric
  consists of two components `metric-queryd` and `metric-collectd` that are both
  narrow in scope.

- FnordMetric is implemented in self-contained C++. It's super quick to set up
  and does not require a lot of resources

- The FnordMetric project was started over 7 years ago and is still actively maintained



## Getting Started

To get started with FnordMetric, have a look at the [Getting Started](/documentation/getting-started) and
[Data Model](/documentation/data-model) pages. If you have any questions please
don't hesitate to reach out via [Github Issues](http://github.com/paulasmuth/fnordmetric/issues)
or [the FnordMetric google group](http://groups.google.com/group/fnordmetric).

<script async defer src="https://buttons.github.io/buttons.js"></script>