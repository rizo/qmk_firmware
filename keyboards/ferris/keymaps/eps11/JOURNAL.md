# Journal

## 2024-05-09

- When a LT key is held with count>1, it will be unpressed when a non-simple (another LT) key is used. There's a ghost event that unpresses the originally held LT key.
- As a workaround, we switch to a different layer on count>1 hold to use a simple key with an override.