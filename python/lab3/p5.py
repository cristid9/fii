def rule_ok(val, rule):
	return val.startswith(rule[1]) and val.endswith(rule[3]) and\
		 	rule[2] in val[1:-1]

def dict_follows_rules(d, rules):
	for k in d:
		r_for_k = [r for r in rules if r[0] == k]
		if len(r_for_k) == 0:
			return False
		for r in r_for_k:
			if not rule_ok(d[k], r):
				return False
			return True

print dict_follows_rules( 
	[
		("key1", "", "inside", ""), 
		("key2", "start", "middle", "winter")
	],  
	{
		"key2": "starting the engine in the middle of the winter", 
		"key1": "come inside, it's too cold outside", "key3": "this is not valid",
		"key3": "bla"
	} 
)

# nu merge
