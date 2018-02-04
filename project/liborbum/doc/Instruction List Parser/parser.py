import pprint
import pyexcel
import json

INPUT_INSTRUCTION_LIST_FILE = 'EE Core Instruction Set.ods'
OUTPUT_PARSED_LOOKUP_TREE_FILE = 'parsed_lookup_tree.json'
ROOT_OPCODE_LOOKUP = 'opcode'
CLASSES_LIST_COLNAMES_ROW = 2
CLASSES_LIST_START_ROW = 2  # After setting colnames row.
INSTRUCTIONS_LIST_COLNAMES_ROW = 2
INSTRUCTIONS_LIST_START_ROW = 3  # After setting colnames row.

lookup_tree = {
    'name': 'OPCODE',
    'type': 'class',
    'lookup_field': ROOT_OPCODE_LOOKUP
}

def get_sheet_cleaned(name, headers_row_index):
    sheet = pyexcel.get_sheet(file_name=INPUT_INSTRUCTION_LIST_FILE, sheet_name=name)
    del sheet.row[lambda _, row: not any(filter(lambda el: el, row))]  # Remove blank rows.
    sheet.name_columns_by_row(headers_row_index)  # Get sheet headers.
    return sheet


def dict_deep_find(key, dict_):
    for k, v in dict_.items():
        if k == key:
            return v
        elif isinstance(v, dict):
            result = dict_deep_find(key, v)
            if result:
                return result
    return None


def build_class_tree(class_entry):
    def insert_entry(base, entry):
        base[entry['Class']] = {
            'type': 'class',
            'name': entry['Class'],
            'value': entry['Value'], 
            'lookup_field': entry['Lookup Field']
        }

    if class_entry['Base Class'] == 'OPCODE':
        insert_entry(lookup_tree, class_entry)
    else:
        # Find the base class by searching the tree.
        base_class_name = class_entry['Base Class']
        base_class = dict_deep_find(base_class_name, lookup_tree)
        if not base_class:
            raise ValueError(f'Base class {base_class_name} not found.')
        insert_entry(base_class, class_entry)


def build_instruction_tree(inst_entry):
    def insert_entry(base, entry):
        base[entry['Instruction']] = {
            'type': 'instruction',
            'name': entry['Instruction'],
            'class_index': entry[base['lookup_field']],
            'impl_index': entry['Index'],
            'cpi': entry['CPI'],
        }

    base_class_name = inst_entry['Class']
    inst_name = inst_entry['Instruction']

    if dict_deep_find(inst_name, lookup_tree):
        raise ValueError(f'Instruction {inst_name} already exists.')

    if base_class_name == 'OPCODE':
        insert_entry(lookup_tree, inst_entry)
    else:
        # Find the base class by searching the tree.
        base_class = dict_deep_find(base_class_name, lookup_tree)
        if not base_class:
            raise ValueError(f'Base class {base_class_name} not found.')
        insert_entry(base_class, inst_entry)


# Get and process classes data.
sheet = get_sheet_cleaned('Classes', CLASSES_LIST_COLNAMES_ROW)
for row in sheet.to_records()[CLASSES_LIST_START_ROW:]:
    build_class_tree(row)

print('Finished processing classes:')
pprint.pprint(lookup_tree)

# Get and process instruction data.
sheet = get_sheet_cleaned('Instructions', INSTRUCTIONS_LIST_COLNAMES_ROW)
for row in sheet.to_records()[INSTRUCTIONS_LIST_START_ROW:]:
    build_instruction_tree(row)

print('Finished processing instructions:')
pprint.pprint(lookup_tree)

with open(OUTPUT_PARSED_LOOKUP_TREE_FILE, 'w') as f:
    json.dump(lookup_tree, f, indent=4)
