from pathlib import Path
from tempfile import NamedTemporaryFile

from ..Common import load_tree, find_text
from lxml.etree import fromstring

def test_load_tree() -> None:
    with NamedTemporaryFile() as temp_file_str:
        temp_file = Path(temp_file_str.name)
        raw_xml = """<?xml version="1.0" encoding="UTF-8"?>
<note>
  <dummy1>Value1</dummy1>
  <dummy2>Value2</dummy2>
  <heading>Some-Header</heading>
  <body>Some content here</body>
</note>"""
        temp_file.write_text(raw_xml)
        tree, root, schema = load_tree(str(temp_file))
        assert isinstance(schema, str)
        assert schema == ""
        assert root.text == "\n  "
        assert tree is not None


def test_find_text_normal_usage() -> None:
    element = fromstring("<Build><BuildType>Dummy</BuildType><bBuild>1</bBuild></Build>")
    found_text = find_text(element=element, schema="", child_element="BuildType")
    assert isinstance(found_text, str)
    assert found_text == "Dummy"

    found_text = find_text(element=element, schema="", child_element="bBuild")
    assert isinstance(found_text, str)
    assert found_text == "1"


def test_find_text_no_result() -> None:
    element = fromstring("<Build><NotBuildType>Dummy</NotBuildType><bBuild>1</bBuild></Build>")
    found_text = find_text(element=element, schema="", child_element="BuildType")
    assert found_text is None
