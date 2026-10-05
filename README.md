# Integration of TOPPRA in HPP

This package was kick-started from the [TOPPRA plugin](https://github.com/humanoid-path-planner/hpp-core/tree/master/plugins) in [hpp-core](https://github.com/humanoid-path-planner/hpp-core).

## Stops

By default, TOPPRA times the whole path continuously. Parameter
`PathOptimization/TOPPRA/stopMethod`, or attribute `stopMethod` in Python,
selects where the robot stops:

| Value | Stops |
| --- | --- |
| `none` | Only at the path ends |
| `subpaths` | Between the subpaths of the input path vector |
| `junctions` | At every leaf junction and interpolation point |

Each portion is timed from rest to rest. `subpaths` suits optimizers that
return one subpath per segment to time, such as
`hpp::manipulation::pathOptimization::ManipulationSpline`, which returns one
subpath per manipulation state. `junctions` preserves the geometry of paths
with corners.

```python
from pyhpp_toppra import Toppra

optimizer = Toppra(problem)
optimizer.stopMethod = "junctions"
timed_path = optimizer.optimize(path)
```

## Instruction for developers

### Unit tests

At the moment, there is no CI pipeline so developpers should make sure the unit test passes
before submitting a PR.

### Increase the version number

Inreasing the version number is done with `bump2version`.
Run `bump2version (major|minor|patch)` depending on the version number you wish to increase.
