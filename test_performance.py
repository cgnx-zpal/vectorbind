import timeit

import_binds = ['import Vector_Opaq_Bind as bind',
                'import Vector_Nano_Bind as bind']
# import_binds = ['import Vector_Nano_Bind as bind',
#                 'import Vector_Opaq_Bind as bind']

testcode_func = '''
def perf(isRef):
  f = bind.FooBigData()
  b = bind.BigData()
  number_of_loop = 10
  for i in range(number_of_loop):
    f.append(b)
    if(isRef):
      assert f.get_items()[i][0] == 0
      bind.increase_b(f.get_items())
    else:
      assert f.get_items_copy()[i][0] == 0
      bind.increase_b(f.get_items_copy())
  if(isRef):
    assert f.get_items()[0][number_of_loop-1] == number_of_loop
    assert f.get_items()[number_of_loop-1][number_of_loop-1] == 1
  else:
    assert f.get_items_copy()[0][number_of_loop-1] == 0                # !!!
    assert f.get_items_copy()[number_of_loop-1][number_of_loop-1] == 0 # !!!
'''

testcode1 = '''
perf(True)
'''
testcode2 = '''
perf(False)
'''

testcodes = [testcode1, testcode2]

def test_PerfVector():
  byRef = True
  for testcode in testcodes:
    if(byRef):
      print("Returns by reference:")
    else:
      print("Returns by value:")
    for import_bind in import_binds:
      setup_code = import_bind + testcode_func
      print("  "+str(timeit.timeit(stmt=testcode, setup=setup_code, number=50)))
    byRef = not byRef
    