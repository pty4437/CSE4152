import React from "react";
import styled from "styled-components";

// 체크된/안된 항목 객체 하나를 한 줄로 보여주기 위한 컴포넌트
function TodoItem({ todo, onRemove, onToggle }) {

  const { id, text, checked } = todo;

  return (
    <Container>
      {/* 체크 버튼 -> todo.checked의 값에 따라 toggle(체크마크 표시 여부)됨 */}
      <DoneButton onClick={() => onToggle(id)}>
        {checked ? <CheckBox src="./img/check.png" /> : null}
      </DoneButton>
      {/* 할일 텍스트 내용 -> todo.checked의 값에 따라 toggle(줄 표시 효과 여부)됨 */}
      <Topic
        style={{
          textDecoration: checked ? "line-through" : null,
          color: checked ? "#ccc" : "#000",
        }}
      >
        {text}
      </Topic>
      <DeleteButton onClick={() => onRemove(id)}>
        <DeleteImg src="./img/trash.png" />
      </DeleteButton>
    </Container>
  );
  
}

// user custom components
const Container = styled.div`
  display: flex;
  flex-direction: row;
  justify-content: center;
  align-items: center;
  margin: 3px 0;
`;

const DoneButton = styled.button`
  display: flex;
  justify-content: center;
  align-items: center;
  width: 30px;
  height: 30px;
  border: 0.1px solid #ccc;
  border-radius: 50%;
  background-color: transparent;
  font-size: 7px;
  cursor: pointer;
  &:focus {
    outline: none;
  }
`;

const CheckBox = styled.img`
  width: 15px;
  height: 15px;
`;

const Topic = styled.p`
  display: flex;
  flex-direction: row;
  align-items: center;
  width: 330px;
  height: 30px;
  padding: 0 10px;
  margin: 0 10px;
  border: 0.8px solid #ccc;
  font-size: 14px;
`;

const DeleteButton = styled.button`
  border: 0;
  background-color: transparent;
  cursor: pointer;
  &:focus {
    outline: none;
  }
`;

const DeleteImg = styled.img`
  width: 25px;
  height: 25px;
`;

export default TodoItem;
