import React, { useState, useRef, useEffect } from "react";
import styled from "styled-components";

function TodoInsert(props) {
  const [content, setContent] = useState("");
  const ref = useRef();

  const handleChange = (e) => {
    // 입력창의 내용이 바뀔 때 state 업데이트
    setContent(e.target.value);
  };

  // Enter 키 누르면 폼 제출
  const handleKeyPress = (e) => {
    if (e.key === "Enter") {
      handleSubmit();
    }
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    // 만약 빈 input 창을 submit을 하려고 할 땐 return
    if (!content) return;
    props.onSubmit(content);
    // submit을 한 후에는 input 창을 비움
    setContent("");
  };

  useEffect(() => {
    ref.current.focus();
  }, []);

  return (
    <Container>
      {/* 전체 폼 양식(입력창 제출하기 위한 양식)감싸는 태그 */}
      <form onSubmit={handleSubmit}>
        {/* 할 일 입력창 */}
        <TextInput
          ref={ref}
          type="text"
          name="text"
          placeholder="할 일을 입력하세요..."
          value={content}
          onChange={handleChange}
        />
        {/* 폼 제출 버튼(Enter 버튼) */}
        <AddButton
          type="submit"
          onClick={handleSubmit}
          onKeyPress={handleKeyPress}
          style={{color: '#415e3e'}}
        >
          ENTER
        </AddButton>
      </form>
    </Container>
  );
}

// user custom components
const Container = styled.div`
  display: flex;
  flex-direction: row;
  justify-content: center;
  align-content: center;
`;

const TextInput = styled.input`
  width: 300px;
  padding: 10px;
  margin: 0 5px;
  border: 0;
  border-bottom: 1px solid #ccc;
  font-size: 16px;
  &:focus {
    outline: none;
  }
  &::placeholder {
    color: #d8e3e7;
    font-style: italic;
  }
`;

const AddButton = styled.button`
  width: 60px;
  height: 32px;
  border: 0;
  border-radius: 5px;
  background-color: #f5c3c5;
  cursor: pointer;
  &:focus {
    outline: none;
  }
`;

export default TodoInsert;
