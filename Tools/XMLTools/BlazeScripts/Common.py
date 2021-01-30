import lxml.etree as ET


# Given path to xml file, return (root, schema) of that file
def load_tree(path_to_xml):
    tree = ET.parse(path_to_xml)
    root = tree.getroot()
    tag = root.tag
    schema = tag[:tag.find('}')+1]  # probably some .attrib way to get it but this works too
    return tree, root, schema


def find_text(element, schema, child_element):
    tag = element.find(f"{schema}{child_element}")
    if tag:
        text = element.find(f"{schema}{child_element}").text
        return text
    return None