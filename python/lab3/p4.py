def build_xml_element(tag, contents, **kwargs):
	attributes = ' '	
	for e in kwargs:
		attributes += e + '="' + kwargs[e] + '" '
	s = '<' + tag + attributes + '>'
	s += contents
	s += '</' + tag + '>'

build_xml_element("a", "Hello there", id="ana")
