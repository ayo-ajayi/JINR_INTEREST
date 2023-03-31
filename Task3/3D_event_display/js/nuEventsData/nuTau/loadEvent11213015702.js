display3d.resetEvent();

display3d.event().id(11213015702);
display3d.event().date(1312179772000);

display3d.event().vertices3D([
  new Vertex([42984.3, 36068.7, 24420.3], [146.342, -177.887, 353.124]),
  new Vertex([42990,   36064.6, 24634.5], [146.343, -177.888, 353.145]),
  new Vertex([43022.4, 36037.4, 24924.3], [146.346, -177.890, 353.174])
]);

display3d.event().tracks3D([
  new Track3D(0, 8,   [42984.3, 36068.7, 24420.3], [1000000., 1000000.], [42990, 36064.6, 24634.5]),
  new Track3D(1, 14,  [42984.3, 36068.7, 24420.3], [1000000., 1000000.], [41953.8, 35123.1, 25908]),
  new Track3D(2, 12,  [43022.4, 36037.4, 24924.3], [1000000., 1000000.], [43462.2, 36209.9, 27198]),
  new Track3D(3, 12,  [43462.2, 36209.9, 27198], [1000000., 1000000.], [43696.3, 36348.6, 28476]),
  new Track3D(4, 12,  [43696.3, 36348.6, 28476], [1000000., 1000000.], [43894, 36484.3, 29756]),
  new Track3D(5, 12,  [43894, 36484.3, 29756], [1000000., 1000000.], [44098.4, 36613.8, 31036]),
  new Track3D(6, 9,   [42990, 36064.6, 24634.5], [1000000., 1000000.], [43141.1, 36052.1, 27198]),
  new Track3D(7, 9,   [43141.1, 36052.1, 27198], [1000000., 1000000.], [43282, 36050.8, 29756]),
  new Track3D(8, 9,   [43282, 36050.8, 29756], [1000000., 1000000.], [43510.8, 36026.6, 33595]),
  new Track3D(9, 15,  [42984.3, 36068.7, 24420.3], [1000000., 1000000.], [43377.9, 36110.7, 25908]),
  new Track3D(10, 15, [43377.9, 36110.7, 25908], [1000000., 1000000.], [43681, 36121.4, 27198]),
  new Track3D(11, 15, [43681, 36121.4, 27198], [1000000., 1000000.], [43982.4, 36078.9, 28476]),
  new Track3D(12, 15, [43982.4, 36078.9, 28476], [1000000., 1000000.], [44308.6, 36022.6, 29756]),
  new Track3D(13, 15, [44308.6, 36022.6, 29756], [1000000., 1000000.], [44674.4, 35982.2, 31036]),
  new Track3D(14, 15, [44674.4, 35982.2, 31036], [1000000., 1000000.], [45015.4, 35970.2, 32295]),
  new Track3D(15, 15, [45015.4, 35970.2, 32295], [1000000., 1000000.], [45353.2, 36009.9, 33595]),
  new Track3D(16, 15, [45353.2, 36009.9, 33595], [1000000., 1000000.], [45699.8, 36029.6, 34885]),
  new Track3D(17, 10, [42990,   36064.6, 24634.5], [1000000., 1000000.], [43040.8, 36503, 28476]),
  new Track3D(18, 10, [43040.8, 36503, 28476], [1000000., 1000000.], [43063.3, 36656, 29756]),
  new Track3D(19, 10, [43063.3, 36656, 29756], [1000000., 1000000.], [43114.9, 36966.1, 32295]),
  new Track3D(20, 10, [43114.9, 36966.1, 32295], [1000000., 1000000.], [43134.1, 37138, 33595]),
  new Track3D(21, 17, [42990,   36064.6, 24634.5], [1000000., 1000000.], [43022.4, 36037.4, 24924.3]),
  new Track3D(22, 11, [43022.4, 36037.4, 24924.3], [1000000., 1000000.], [43173.54, 36131.21, 24490]),
  new Track3D(23, 16, [43022.4, 36037.4, 24924.3], [1000000., 1000000.], [43244.33, 35909.28, 24490]),
  new Track3D(24, 13, [43022.4, 36037.4, 24924.3], [1000000., 1000000.], [43396.22, 35954.37, 25300])
]);

display3d.mgrDraw3D().onEventChange();