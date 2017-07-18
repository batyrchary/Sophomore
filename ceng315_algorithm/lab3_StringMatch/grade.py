import subprocess
def helper(text, flag):
	text = text.rstrip()
	entries = text.split(' ')
	if entries[-1] == '':
		entries = entries[:-1]
	return map(int, entries) if flag else entries

def evaluate(text, pattern, cs, solution):
	cs = helper(cs, False)
	solution = helper(solution, True)
	try:
		p = subprocess.Popen(['timeout', '1', './evaluate'], 
			stdin=subprocess.PIPE,
			stdout=subprocess.PIPE)
		studentOutput, stderr = p.communicate('%d %d %s %s %s %s' % (len(text), len(pattern), text, pattern, cs[0], cs[1]))
		if '\x01\x01\x01' not in studentOutput:
			output = 'Segmentation Fault\n'
			grade = 0
		else:
			studentOutput = studentOutput.split('\x01\x01\x01')[1]
			studentSolution = sorted(helper(studentOutput, True))
			_studentSolution = ' '.join(map(str, studentSolution[:len(text)])) + ('...' if len(studentSolution) > len(text) else '')
			if len(solution) != len(studentSolution):
				output = "Size mismatch\n"
				output += "Expected solution: %s\n" % (' '.join(map(str, solution)), )
				output += "Student solution:  %s\n" % _studentSolution
				grade = 0
			else:
				for s1, s2 in zip(studentSolution, solution):
					if s1 != s2:
						output = "Output differ\n"
						output += "Expected solution: %s\n" % (' '.join(map(str, solution)), )
						output += "Student solution:  %s\n" % _studentSolution
						grade = 0
						break
		
				else:
					output = "Success\n"
					grade = 1
	except:
		output = "Failed, unknown reason\n"
		grade = 0
	print output
	return grade
	
def main(textFile, patternFile, csFile, solutionFile):
	with open(textFile) as f:
		texts = f.read().split('\n')[:-1]
	with open(patternFile) as f:
		patterns = f.read().split('\n')[:-1]
	with open(csFile) as f:
		css = f.read().split('\n')[:-1]
	with open(solutionFile) as f:
		solutions = f.read().split('\n')[:-1]
       	grade = 0.0
	for i, (t, p, c, s) in enumerate(zip(texts, patterns, css, solutions)):
		print 'Test case %d:' % i,
		grade += evaluate(t, p, c, s)
	grade /= len(solutions)
	grade *= 100
	print 'Grade: %.2f' % grade

if __name__ == '__main__':
	import sys
	try:
		main(*sys.argv[1:])
	except:
		print "Usage: python %s <path_to_texts_file> <path_to_patterns_file> <path_to_css_file> <path_to_solutions_file>" % sys.argv[0]
		print "Please place 'evaluate' file compiled by makefile to this folder"
