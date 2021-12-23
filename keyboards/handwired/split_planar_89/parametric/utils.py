from key import *
import cadquery


# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


class KeyUtils(object):

    @staticmethod
    def set_position_relative_to(key: KeyBase, ref_key: KeyBase, pos: Direction) -> None:
        """
        Sets the key position as being top/bottom and left/right of the reference key.
        """
        if pos == Direction.TOP:
            key.position = (
                ref_key.position[0],
                ref_key.position[1] + ref_key.depth / 2 + ref_key.clearance_top + key.clearance_bottom + key.depth / 2,
                key.position[2])

        elif pos == Direction.BOTTOM:
            key.position = (
                ref_key.position[0],
                ref_key.position[1] - ref_key.depth / 2 - ref_key.clearance_bottom - key.clearance_top - key.depth / 2,
                key.position[2])

        elif pos == Direction.RIGHT:
            key.position = (
                ref_key.position[0] + ref_key.width / 2 + ref_key.clearance_right + key.clearance_left + key.width / 2,
                ref_key.position[1],
                key.position[2])

        elif pos == Direction.LEFT:
            key.position = (
                ref_key.position[0] - ref_key.width / 2 - ref_key.clearance_left - key.clearance_right - key.width / 2,
                ref_key.position[1],
                key.position[2])

        else:
            assert False

    @staticmethod
    def connector(first_face: cadquery.Workplane, second_face: cadquery.Workplane) -> cadquery.Workplane:
        """
        Returns a loft/gap filler in between two faces.
        @param first_face:
        @param second_face:
        """

        def get_wire(face):
            return face.first().wires().val()

        return cadquery.Workplane(cadquery.Solid.makeLoft([get_wire(first_face), get_wire(second_face)]))

    @staticmethod
    def key_connector(first_key: Key,
                      second_key: Key,
                      first_direction: Direction,
                      second_direction: Direction) -> cadquery.Workplane:
        """
        Returns a loft/gap filler in between two key faces as specified the direction.
        @param first_key: the key to loft from
        @param second_key: the key to loft to
        @param first_direction: the face to loft from
        @param second_direction: the face to loft to
        """

        def get_wire(face):
            return face.first().wires().val()

        first_wire = get_wire(first_key.slot.get_cad_face(first_direction))
        second_wire = get_wire(second_key.slot.get_cad_face(second_direction))
        return cadquery.Workplane(cadquery.Solid.makeLoft([first_wire, second_wire]))

    @staticmethod
    def connect_keys(connection_info: List[Tuple[int, int, Direction, int, int, Direction]],
                     key_matrix: List[List[Key]]) -> None:
        """
        Creates solids for gaps in between the keys as listed in the connection info.
        @param connection_info: information which keys to connect and which faces to use
        @param key_matrix: pool of keys with pre-computed placement and cad objects
        """
        print("compute key to key connectors ({}) ...".format(len(connection_info)))

        for a_row, a_idx, a_direction_x, b_row, b_col, b_direction_x in connection_info:
            a = key_matrix[a_row][a_idx]
            b = key_matrix[b_row][b_col]
            if a.slot.has_cad_object() and b.slot.has_cad_object():
                print(".", end="")
                loft = KeyUtils.key_connector(a, b, a_direction_x, b_direction_x)
                a.connectors.get_connector(a_direction_x)._cad_object = loft
                b.connectors.get_connector(b_direction_x)._cad_object = loft

                a.expose_cad_objects()
                b.expose_cad_objects()
            else:
                print("x", end="")
        print("\ncompute key to key connectors: done")

    @staticmethod
    def connect_connectors(connection_info: List[Tuple[int, int, Direction, Direction, int, int, Direction, Direction]],
                           key_matrix: List[List[Key]]) -> None:
        print("compute connector gap filler ({}) ...".format(len(connection_info)))
        for a_row, a_idx, a_direction_x, a_direction_y, b_row, b_col, b_direction_x, b_direction_y in connection_info:
            a = key_matrix[a_row][a_idx]
            b = key_matrix[b_row][b_col]

            a_connector = a.connectors.get_connector(a_direction_x)
            b_connector = b.connectors.get_connector(b_direction_x)
            if a_connector.has_cad_object() and b_connector.has_cad_object():
                print(".", end="")
                a_connector = a.connectors.get_connector(a_direction_x)
                b_connector = b.connectors.get_connector(b_direction_x)
                loft = KeyUtils.connector(
                    a_connector.get_cad_face(a_direction_y),
                    b_connector.get_cad_face(b_direction_y))
                a.connectors.get_connector(a_direction_y)._cad_object = loft
                b.connectors.get_connector(b_direction_y)._cad_object = loft

                a.expose_cad_objects()
                b.expose_cad_objects()
            else:
                print("x", end="")
        print("\ncompute connector gap filler: done")

    @staticmethod
    def remove_cad_objects(key_matrix: List[List[Key]], remove_non_solids: bool) -> None:
        """
        Filters out cad objects from view that must be computed due to dependencies but shall not be rendered.
        @param key_matrix: pool of keys with pre-computed placement and cad objects
        @param remove_non_solids: removes also objects such as placement, name or origin if True
        """
        row_idx = 0
        print("removing cad objects ...")
        for row in key_matrix:
            print("row {}".format(row_idx))
            for key in row:
                print("  {:7}: ".format(key.name), end=" ")
                if not GlobalConfig.debug.render_placement or remove_non_solids:
                    key.cad_objects.plane = None
                    print("placement", end=" ")
                if not GlobalConfig.debug.render_origin or remove_non_solids:
                    key.cad_objects.origin = None
                    print("origin", end=" ")
                if not GlobalConfig.debug.render_name or remove_non_solids:
                    key.cad_objects.name = None
                    print("name", end=" ")
                if not GlobalConfig.debug.render_cap:
                    key.cad_objects.cap = None
                    print("cap", end=" ")
                if not GlobalConfig.debug.render_slots:
                    key.cad_objects.slot = None
                    print("slot", end=" ")
                if not GlobalConfig.debug.render_switch:
                    key.cad_objects.switch = None
                    print("switch", end=" ")
                if not GlobalConfig.debug.render_connectors:
                    key.cad_objects.connectors = []
                    print("connectors", end=" ")
                print("")
            row_idx += 1
        print("removing cad objects: done")

    @staticmethod
    def squash(key_matrix: List[List[Key]], do_unify: bool, do_clean_union: bool) -> Union[cadquery.Workplane, cadquery.Assembly]:
        """
        Squashes all available cad objects of any key to one unified compound or assembly.
        @param key_matrix: pool of keys with pre-computed placement and cad objects
        @param do_unify: recommended True for step file, False for cadquery editor (cq-editor)
        @param do_clean_union: recommended False for prototyping, True has weak the performance
        @return cadquery.Workplane if do_unify else cadquery.Assembly
        """
        print("final assembly ({}) ...".format("union" if do_unify else "assembly"))
        assembly = cadquery.Assembly()
        union = cadquery.Workplane()  # type: cadquery.Workplane

        row_idx = 0
        for row in key_matrix:
            print("row {}".format(row_idx))
            for key in row:
                color = cadquery.Color(0, 0, 1, 0.5) if key.base.is_visible else cadquery.Color(1, 1, 1, 0.125)
                print("  {:7}:".format(key.name), end=" ")
                if not key.base.is_visible and not GlobalConfig.debug.show_invisibles:
                    continue

                # key components
                for object_name, cad_object in [(attr_name, value) for attr_name, value in key.cad_objects]:
                    if type(cad_object) is list:
                        continue
                    print("{}".format(object_name), end=" ")
                    if do_unify:
                        union = union.union(cad_object, clean=do_clean_union)
                    else:
                        assembly = assembly.add(cad_object, color=color)

                # connectors
                for connector in key.cad_objects.connectors:
                    print("connector", end=" ")
                    if do_unify:
                        union = union.union(connector, clean=do_clean_union)
                    else:
                        assembly = assembly.add(connector, color=color)
                print("")
            row_idx += 1
        print("final assembly ({}): done".format("union" if do_unify else "assembly"))
        return union if do_unify else assembly
