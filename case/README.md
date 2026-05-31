# SuperSensor v3.x Case

This is a 3D-printable case/enclosure for the SuperSensor v3.0 module. This case is recommended for proper sensor operation, and for aesthetics and mounting purposes, but is not strictly required.

The design features several individual parts:

* A body with standoffs to hold the assembled PCB with openings for ventilation and the USB connections on the right side (facing the sensor).
* A cover with holes for the microphone (conical focusing), the PIR (w/lens), and the LED insert, along with a back cover for the descender.
* An LED insert diffuser with a hole for the UESM.
* A wall-mount assembly featuring two 45+° securable ball joints and 3 mounting options.
* A table-mount assembly featuring one 45+° securable ball joint and a flat bottom including cutouts for 4 ~13mm rubber anti-slip feet.

You can [tinker the design on TinkerCAD here](https://www.tinkercad.com/things/gx66mJQMgR6).

The case design and images in this folder are © 2025 [Joshua M. Boniface](https://www.boniface.me) and licensed under the [Creative Commons Attribution-ShareAlike (BY-SA) 4.0](LICENSE) license. The design contains elements from [Nikolay "darkfrei"'s Universal Ball Joint design](https://www.thingiverse.com/thing:6804839) for the mounting components, provided under the same license.

* [Printing](#printing)
   * [Main Case Models](#main-case-models)
   * [Mounting Models](#mounting-models)
* [Assembly & Installation](#assembly--installation)
   * [Case Assembly](#case-assembly)
   * [Mount Assembly (Common)](#mount-assembly-common)
   * [Mount Assembly & Installation (Table)](#mount-assembly--installation-table)
   * [Mount Assembly & Installation (Wall)](#mount-assembly--installation-wall)

## Printing

In this directory are 8 `.obj`-format CAD files collectively providing the case and mounting system. They should be compatible as-is with any slicing software and 3D printer model; no rotation or other transformations are required.

As a general set of parameters, all models should be printed with the following, **except** for any differences specified in specific models below. All values are provided as their OrcaSlicer 2.3 names; your slicer may differ.

* 0.16mm layer height, or a clean multiple
* No brim or raft
* Tree supports
* Supports touching buildplate only
* 0.8mm Support/object first layer gap
* 7-10 wall loops
* 7-10 shell layers (top + bottom)
* 25% infill
* Concentric patterns for infill
* Concentric patterns for surfaces (visual only)
* Back (preferred) or Aligned seams (visual only)

All other options are specific to your printer, material, and desired effect and can be adjusted as needed.

The parts should be printed in a solid, durable material of any colour you wish, except for the insert as noted below. We use white or black ABS (depending on the aesthetics of the final location) for our official prints.

### Main Case Models

These are the primary models that make up the case. Each case requires 1x `case-body`, 1x `case-cover`, and 1x `case-insert`.

#### `case-body`

This is the main body of the case which houses the assembled sensor PCB. It includes a large side opening for the insertion of a USB-C cable of "normal" size into either ESP32-S3 input, which should fit most cables.

#### `case-cover`

This is the front face of the case. It clips into the body with 4 triangular grip clips (2 each on the top and bottom). It features 3 openings for components:

  * A 7.6mm conical opening for the microphone.
  * An 10.4 mm diameter circular opening for the SR602 PIR and lens.
  * A 57.2 x 9.2 mm rectangular opening, with a center 14.4 mm circular protrusion, for the LED cover below.

It also features a "decender" feature that covers the protrusion of the UESM for the SHT45 temperature sensor, with a square opening for the SHT45 itself, as well as a small press-fit cover for the back of this feature.

#### `case-insert`

This insert fits into the large rectangle in the cover, and provides a diffuser for the feedback/status LEDs, an opening for the UESM's circular component, and cutouts for the UESM's protrusion.

This part is inserted into the face separately during assembly, though a multi-material printer could concievably print it directly into the face during printing (with modifications to adjust the height accordingly).

This part should be printed in a solid, durable material of **a natural, transluscent, or transparent** colour (it must let white light through reasonably well). We use transparent ABS in for our official prints.

### Mounting Models

These models provide mounting options for the case in various configurations depending on your environment. These models are completely optional should you wish to devise your own mounting scheme, but two common configurations are provided:

* A wall/ceiling mount with ~100° of adjustment freedom across two ball joints; each mount requires 2x `mount-ball`, 2x `mount-nut`, 1x `mount-tube`, and 1x of **either** `mount-base-adhesive`, `mount-base-screw`, or `mount-base-ties.
* A table/desk mount with ~50° of adjustment freedom across a single ball joint; each mount requires 1x `mount-ball`, 1x `mount-nut`, and 1x `mount-base-table`.

#### `mount-ball`

This is a ball and rod for a ball joint with a flanged (conical) bottom, for attaching to the `case-body` back and, for wall mounts, the `mount-ball-base` below.

This part requires **10 wall loops** for optimal strength and **random seams** to avoid excessive binding in any one position.

#### `mount-nut`

This is a nut for the `mount-ball` to connect it to either the `mount-extension-tube` or the `mount-table-base` below. It goes between the ball and either the `case-body` or `mount-ball-base` with the thread openingfacing out (towards the ball); final assembly to another part locks it into place permanently.

#### `mount-base-table`

This is a flat-based riser with a sleek profile and a single screw-end at the top to attach a ball joint to. The model features rounded corners and a swoop up into the riser for style reasons, as well as 4 bottom indents to attach ~13 mm diameter rubber feet for traction.

This part _may_ require a **brim** depending on material properties; for our ABS prints a 110°C build plate temperature counteracts this, but your material may differ.

#### `mount-base-adhesive`

This is a base for the `mount-ball` part when used as part of a wall mount, to affix it to the wall via an adhesive layer like a 3M Command™ strip. It features an indent sized to accept the conical base of the `mount-ball` part.

#### `mount-base-screws`

This is a base for the `mount-ball` part when used as part of a wall mount, to affix it to the wall via a pair of M4 or #6 wood screws. It features an indent sized to accept the conical base of the `mount-ball` part, and two countersunk holes that should fit the aforementioned screw heads.

#### `mount-base-ties`

This is a base for the `mount-ball` part when used as part of a wall mount, to affix it to an object with a pair of ~6mm cable ties. It features an indent sized to accept the conical base of the `mount-ball` part, and two countersunk rectangular holes that should fit the aforementioned cable ties.

#### `mount-tube`

This is a double screw-ended tube which connects the two ball joints in the wall/ceiling mount; it is not required for the table/desk mount.

This part requires a **brim** or it has a habit of popping off the build plate mid-print.

There are two variations of this part: `-10mm` has a 10mm grip, while `-15mm` has a 15mm grip. We personally use 10mm as the default, but if you want the extra range of angle afforded by the extra length you may use the 15mm version.

## Assembly & Installation

To begin, print the parts above as required for the specific mounting type you want.

For proper assembly & installation, you will also need:

* Cyanoacrylate superglue, to join several components depending on your configuration; a precision applicator is ideal.

* For the adhesive wall mount, one 3M Command™ strip (Medium size, or similar double-sided wall-safe adhesive) is required, to affix the second ball joint mount to a wall, ceiling, or other location while permitting non-destructive removal.

* For the screw wall mount, two M4/#6 wood screws with tapered heads are required.

* For the table mount, circular rubber feet (~13mm or less in diameter) are recommended to avoid slipping, but are not required; there are indents for optimal placement.

### Case Assembly

1. Construct a SuperSensor board with all components.

2. Insert the `case-insert` into the opening of the `case-cover`, applying steady, even pressure face-down against a surface to fully seat it. Due to overextrusion, the fit may sometimes be tight, and trimming may be required for optimal fit. Cyanoacrylate superglue can also help ensure stability if the insert will not fit snugly.

3. Take the `case-body` and insert the SuperSensor board such that it aligns with the 4 standoffs and the USB connectors with the opening at the bottom of the case. The board should press cleanly down onto them.

4. Remove the cap (both pieces, exposing the raw PIR element) from the SR602 PIR sensor.

5. Take the `case-cover` and place it over the UESM board and PIR sensor, aligning it with protruding sensors and the `case-body`.

6. Insert the `case-cover` latches into one side of the `case-body`, and then gently flex it to press down the latches on the other side; it should snap nicely into place securing the cover to the body. Readjust the sensor modules such that they are fully inside the holes.

7. Align and gently press the cap back onto the SR602 PIR sensor until it is seated well, avoiding pressing down on the non-pin side; seating on an angle may help. Once aligned press down firmly to fully seat it.

### Mount Assembly (Common)

1. Take the `mount-nut` and place one of/the `mount-ball` into it with the screw opening facing the ball (the same orientation they are printed); the nut should become captive on the ball while being able to screw into the other components.

2. Apply a small dab of superglue onto the bottom of the `mount-ball` conical rod.

3. Take the completed case assembly, and turn it around to the back. Press the glued surface of the `mount-ball` into the hatched "recess" in the `case-body`, gently turn it at least 1/4 turn, then allow the glue to cure.

### Mount Assembly & Installation (Table)

**Warning:** Never overtighten the ball nut! You want it tight enough so that it won't drift, but not so tight as to crack the plastic.

1. Apply rubber feet to the mounting inserts on the bottom of the `mount-base-table` if desired.

2. Take your `mount-base-table` and your `mount-nut` + `mount-ball` + case, and screw the nut onto the screw portion of the riser. The ball should become captive, but do not fully tighten it yet.

3. Place the completed unit in the desired location, and adjust the sensor to point where you would like, slowly tightening the nut as you adjust.

4. Once you are happy with the direction, tighten the nut a little more while firmly holding the unit so it does not twist; you may need to "preload" the position slightly to work with the nut pulling the ball with it.

5. Perform any final fine manual adjustments gently, then apply a little more pressure onto the nut to lock it fully into place.

### Mount Assembly & Installation (Wall)

**Warning:** Never overtighten the ball nuts! You want it tight enough so that it won't drift, but not so tight as to crack the plastic.

1. Take the `mount-nut` and place the remaining `mount-ball` into it with the screw opening facing the ball; the nut should become captive on the ball while being able to screw into the other components.

2. Apply a small dab of superglue onto the bottom of the `mount-ball` conical rod.

3. Take the `mount-base-adhesive`, `mount-base-screws`, or `mount-base-ties` (whichever you printed) and press the glued surface of the `mount-ball` into the recess in the base, rotating it in place several times to ensure optimal glue coverage and that the ball is level with the base, then allow the glue to cure.

4. Take your `mount-tube` and your `mount-nut` + `mount-ball` + case, and screw the nut onto one end of the `mount-tube`. The ball should become captive, but do not fully tighten it yet.

5. Take your combined `mount-tube` + case assembly, and screw the nut from the second `mount-ball` onto it, creating a single line with the case at one end, the `mount-tube` in the center, and the base at the other end. Do not fully tighten either nut yet.

6. Affix a 3M Command™ strip (Medium, or substitute) to the back of the base if applicable.

7. Prepare the surface wall/ceiling/etc. to accept the 3M Command™ strip (or substitute), then adhere the base to the surface, if applicable.

8. Adjust the sensor to point in roughly the direction you wish it to, and secure one nut; this will be your "gross" adjustment.

9. Adjust the sensor further to the exact position while gradually tightening the other nut to lock it into position, firmly holding the unit so it does not twist; you may need to "preload" the position slightly to work with the nut pulling the ball with it.

5. Perform any final fine manual adjustments gently, then apply a little more pressure onto the nuts to lock them fully into place.
