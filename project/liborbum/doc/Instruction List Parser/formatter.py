import json

INPUT_PARSED_LOOKUP_TREE_FILE = 'parsed_lookup_tree.json'
OUTPUT_SOURCE_FILE = 'Lookup.cpp'
OUTPUT_TABLE_FILE = 'Table.cpp'
DEFAULT_NOT_FOUND = 'throw std::runtime_error("Could not determine instruction");'

def write_line(level, text):
    out_file.write('    ' * level)
    out_file.write(text)
    out_file.write('\n')


def start_class(level, class_):
    write_line(level, 'case ' + str(class_['value']) + ':')
    write_line(level, '{')
    write_line(level + 1, 'switch (inst.' + class_['lookup_field'] + '())')
    write_line(level + 1, '{')


def end_class(level):
    write_line(level + 1, 'default:')
    write_line(level + 2, DEFAULT_NOT_FOUND)
    write_line(level + 1, '}')
    write_line(level, '}')


def write_instruction(level, inst):
    instruction_lookup_table.append(inst)
    write_line(level, 'case ' + str(inst['class_index']) + ':')
    write_line(level + 1, f'return &INSTRUCTION_TABLE[{len(instruction_lookup_table) - 1}];')


def write_traverse_lookup_tree(level, base):
    for k, v in base.items():
        if isinstance(v, dict):
            if v['type'] == 'class':
                start_class(level, v)
                write_traverse_lookup_tree(level + 1, v)
                end_class(level)
            elif v['type'] == 'instruction':
                write_instruction(level, v)
            else:
                raise ValueError('Unrecognised type')


instruction_lookup_table = []

# Load in instruction tree.
with open(INPUT_PARSED_LOOKUP_TREE_FILE, 'r') as f:
    lookup_tree = json.load(f)

# Write out lookup proceedure.
out_file = open(OUTPUT_SOURCE_FILE, 'w')
write_line(0, 'MipsInstructionInfo lookup(const MipsInstruction & inst)')
write_line(0, '{')
root_lookup_field = lookup_tree['lookup_field']
write_line(1, f'switch (inst.{root_lookup_field}())')
write_line(1, '{')
write_traverse_lookup_tree(1, lookup_tree)
write_line(1, 'default:')
write_line(2, DEFAULT_NOT_FOUND)
write_line(1, '}')
write_line(0, '}')
out_file.close()

# Write out instruction table (C array).
out_file = open(OUTPUT_TABLE_FILE, 'w')
write_line(0, f'MipsInstructionInfo INSTRUCTION_TABLE[{len(instruction_lookup_table)}] =')
write_line(0, '{')
for inst in instruction_lookup_table:
    write_line(1, '{ "' + inst['name'] + '", ' + str(inst['impl_index']) + ', ' + str(inst['cpi']) + ' },')
write_line(0, '};')
out_file.close()
