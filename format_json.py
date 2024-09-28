import requests
import json

def sort_dict_keys_case_insensitive(d):
    """ Recursively sort dictionary keys alphabetically in a case-insensitive manner. """
    if isinstance(d, dict):
        return {k: sort_dict_keys_case_insensitive(v) for k, v in sorted(d.items(), key=lambda item: item[0].lower())}
    elif isinstance(d, list):
        return [sort_dict_keys_case_insensitive(i) for i in d]
    else:
        return d

def remove_duplicate_dicts(lst):
    """ Remove duplicate dictionaries from a list, preserving order. """
    seen = []
    result = []
    for item in lst:
        if isinstance(item, dict):
            if item not in seen:
                seen.append(item)
                result.append(item)
        else:
            result.append(item)
    return result

def remove_empty_properties(d):
    """
    Recursively remove dictionary properties where all values are None or empty strings.
    Remove lists where all elements are empty strings or None.
    If a dictionary has only empty lists/None values, the key is removed.
    """
    if isinstance(d, dict):
        cleaned_dict = {}
        for k, v in d.items():
            cleaned_value = remove_empty_properties(v)
            # If the cleaned value is not an empty list, string, or None, retain it
            if cleaned_value != "" and cleaned_value is not None and cleaned_value != []:
                cleaned_dict[k] = cleaned_value
        return cleaned_dict
    elif isinstance(d, list):
        # Process each element in the list
        processed_list = [remove_empty_properties(i) for i in d]
        # Remove lists where all elements are empty strings or None
        if all(x == '' or x is None for x in processed_list):
            return None
        return processed_list
    else:
        return d

# Step 1: Perform GET request
url = "https://coderbyte.com/api/challenges/json/date-list"
response = requests.get(url)
data = response.json()

# Step 2: Sort object keys alphabetically in a case-insensitive way
sorted_data = sort_dict_keys_case_insensitive(data)

# Step 3: Remove duplicate dictionaries from lists
def process_lists_for_duplicates(d):
    """ Recursively process lists and remove duplicate dictionaries. """
    if isinstance(d, dict):
        return {k: process_lists_for_duplicates(v) for k, v in d.items()}
    elif isinstance(d, list):
        return remove_duplicate_dicts([process_lists_for_duplicates(i) for i in d])
    else:
        return d

unique_data = process_lists_for_duplicates(sorted_data)

# Step 4: Remove dictionary properties with all values set to empty strings or None, and handle empty lists
cleaned_data = remove_empty_properties(unique_data)

# Step 5: Convert the final data back to JSON format and print
# Ensure we don't pass None at the top level, since the top-level structure should still be preserved as an object
if cleaned_data is None:
    cleaned_data = {}

print(json.dumps(cleaned_data, indent=2))
