"""Python bindings of the TOPPRA path optimizer."""

import unittest

import numpy as np
from pinocchio import SE3
from pyhpp.core import Problem, StraightPath, interval
from pyhpp.core.path import Vector
from pyhpp.pinocchio import Device, urdf
from pyhpp_toppra import Toppra

URDF = """<robot name="arm">
  <link name="base"/><link name="tip"/>
  <joint name="joint" type="revolute">
    <parent link="base"/><child link="tip"/><axis xyz="0 0 1"/>
    <limit lower="-2" upper="2" velocity="1" effort="1"/>
  </joint>
</robot>"""


class TestToppra(unittest.TestCase):
    def setUp(self):
        self.robot = Device("arm")
        urdf.loadModelFromString(
            self.robot, 0, "arm", "anchor", URDF, "", SE3.Identity()
        )
        self.toppra = Toppra(Problem(self.robot))
        self.toppra.velocityScale = 0.5
        self.toppra.accelerationLimits = np.array([0.5])
        self.toppra.N = 100
        self.toppra.selectJoints(["arm/joint"])

    def path(self, *configurations):
        """Path vector of straight paths of unit length between configurations."""
        path = Vector(1, 1)
        for q0, q1 in zip(configurations, configurations[1:]):
            path.appendPath(
                StraightPath(
                    self.robot,
                    np.array([q0]),
                    np.array([q1]),
                    interval(0.0, 1.0),
                    None,
                )
            )
        return path

    def junction_speed(self, stop_method):
        self.toppra.stopMethod = stop_method
        timed = self.toppra.optimize(self.path(0.0, 0.4, 0.8))
        self.assertEqual(timed.numberPaths(), 2)
        first = timed.pathAtRank(0)
        np.testing.assert_allclose(first.end(), [0.4], atol=1e-10)
        np.testing.assert_allclose(timed.end(), [0.8], atol=1e-10)
        for t in np.linspace(0.0, timed.length(), 201):
            self.assertLessEqual(abs(timed.derivative(float(t), 1)[0]), 0.5 + 1e-8)
            self.assertLessEqual(abs(timed.derivative(float(t), 2)[0]), 0.5 + 1e-8)
        for t in (0.0, timed.length()):
            self.assertLess(abs(timed.derivative(t, 1)[0]), 1e-8)
        return abs(first.derivative(first.length(), 1)[0])

    def test_parameters(self):
        self.toppra.stopMethod = "subpaths"
        self.assertEqual(self.toppra.stopMethod, "subpaths")
        self.assertEqual(self.toppra.velocityScale, 0.5)
        self.assertEqual(self.toppra.N, 100)
        np.testing.assert_array_equal(self.toppra.accelerationLimits, [0.5])

    def test_stop_methods(self):
        self.assertGreater(self.junction_speed("none"), 0.1)
        self.assertLess(self.junction_speed("junctions"), 1e-8)
        self.assertLess(self.junction_speed("subpaths"), 1e-8)

    def test_invalid_stop_method(self):
        self.toppra.stopMethod = "everywhere"
        with self.assertRaisesRegex(ValueError, "Invalid stopMethod"):
            self.toppra.optimize(self.path(0.0, 0.4))


if __name__ == "__main__":
    unittest.main()
