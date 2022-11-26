from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional

DESCRIPTOR: _descriptor.FileDescriptor

class DwcRequest(_message.Message):
    __slots__ = ["words"]
    WORDS_FIELD_NUMBER: _ClassVar[int]
    words: _containers.RepeatedScalarFieldContainer[str]
    def __init__(self, words: _Optional[_Iterable[str]] = ...) -> None: ...

class DwcResponse(_message.Message):
    __slots__ = ["word_frequency"]
    class WordFrequencyEntry(_message.Message):
        __slots__ = ["key", "value"]
        KEY_FIELD_NUMBER: _ClassVar[int]
        VALUE_FIELD_NUMBER: _ClassVar[int]
        key: str
        value: int
        def __init__(self, key: _Optional[str] = ..., value: _Optional[int] = ...) -> None: ...
    WORD_FREQUENCY_FIELD_NUMBER: _ClassVar[int]
    word_frequency: _containers.ScalarMap[str, int]
    def __init__(self, word_frequency: _Optional[_Mapping[str, int]] = ...) -> None: ...
