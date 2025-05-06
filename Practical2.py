class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None

class HashTable:
    def __init__(self, capacity=10, replacement=False):
        self.capacity = capacity
        self.table = [None] * capacity
        self.size = 0
        self.replacement = replacement

    def _hash(self, key):
        return hash(key) % self.capacity

    def insert(self, key, value):
        index = self._hash(key)
        new_node = Node(key, value)

        if self.table[index] is None:
            self.table[index] = new_node
            self.size += 1
            return

        current = self.table[index]
        prev = None

        while current:
            if current.key == key:
                if self.replacement:
                    current.value = value
                    return
                else:
                    raise KeyError(f"Key '{key}' already exists.")

            prev = current
            current = current.next

        prev.next = new_node
        self.size += 1

    def find(self, key):
        index = self._hash(key)
        current = self.table[index]

        while current:
            if current.key == key:
                return current.value
            current = current.next

        return None

    def delete(self, key):
        index = self._hash(key)
        current = self.table[index]
        prev = None

        while current:
            if current.key == key:
                if prev:
                    prev.next = current.next
                else:
                    self.table[index] = current.next
                self.size -= 1
                return
            prev = current
            current = current.next

        raise KeyError(f"Key '{key}' not found.")

    def __len__(self):
        return self.size

    def __str__(self):
        result = "{"
        for i in range(self.capacity):
            current = self.table[i]
            while current:
                result += f"'{current.key}': '{current.value}', "
                current = current.next

        if self.size > 0:
            result = result[:-2]
        result += "}"
        return result

# Example Usage with Replacement
ht_replace = HashTable(capacity=5, replacement=True)
ht_replace.insert("apple", 1)
ht_replace.insert("banana", 2)
ht_replace.insert("cherry", 3)
ht_replace.insert("date", 4)
ht_replace.insert("elderberry", 5)

print("HashTable with replacement:", ht_replace)
print("Find 'banana':", ht_replace.find("banana"))

ht_replace.insert("banana", 22) # Replace existing value
print("HashTable with replacement after banana replacement:", ht_replace)

ht_replace.delete("cherry")
print("HashTable with replacement after cherry deletion:", ht_replace)

# Example Usage without Replacement
ht_no_replace = HashTable(capacity=5, replacement=False)
ht_no_replace.insert("apple", 1)
ht_no_replace.insert("banana", 2)
ht_no_replace.insert("cherry", 3)
ht_no_replace.insert("date", 4)
ht_no_replace.insert("elderberry", 5)

print("\nHashTable without replacement:", ht_no_replace)
print("Find 'date':", ht_no_replace.find("date"))

try:
  ht_no_replace.insert("banana", 22)
except KeyError as e:
  print(e)

ht_no_replace.delete("cherry")
print("HashTable without replacement after cherry deletion:", ht_no_replace)


