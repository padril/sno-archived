### Types
Specially implemented types used across the code go in here.
`types.h` automatically includes all of them.

If you want ==Literal== then you should include `types.h`

#### ORDER:
- [ ] Administrative
    - [x] Null
    - [ ] Identifier
- [ ] Ordinal
    - [x] Boolean
    - [x] Countable
        - [x] Integer
        - [x] Rational
    - [ ] Uncountable
        - [x] Real
        - [ ] Complex
- [x] Categorical
    - [x] String
- [ ] Array-like
    - [ ] Ordinal Array
        - [ ] Vector
        - [ ] Matrix
        - [ ] Interval
    - [ ] Categorical Array
        - [ ] List
- [ ] Set
    - [x] Filter
    - [ ] Multiset
        - [ ] Sequence
        - [ ] Function
