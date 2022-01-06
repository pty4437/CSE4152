import React from "react";
import styled from "styled-components";

import TodoInsert from "./TodoInsert";
import TodoItem from "./TodoItem";

// 화면 좌측 WHAT TO DO 부분
function WhatTodo({ handleSubmit, todos, onRemove, onToggle}) {

  return (
    <Container>
      <h1 style={{color: '#415e3e'}}>WHAT TO DO</h1>
      {/* 할일 항목 입력 컴포넌트 */}
      <TodoInsert onSubmit={handleSubmit} />
      {/* 인자로 받은 todos의 각 항목(체크안된 항목) 객체를 가지고 TodoItem 컴포넌트를 생성해서 입력창 밑에 리스트로 보여줌 */}
      <TodoListContainer>
        {todos.map((todo) => {
          return <TodoItem todo={todo} key={todo.id} onRemove={onRemove} onToggle={onToggle}/>
        })}
      </TodoListContainer>
    </Container>
  );

}

// user custom components
const Container = styled.div`
  display: flex;
  flex-direction: column;
  width: 400px;
  height: 400px;
  background-color: #fff;
`;

const TodoListContainer = styled.div`
  display: flex;
  flex-direction: column;
  padding: 10px;
  margin: 20px 10px;
  height: 350px;
  overflow-y: scroll;
`;

export default WhatTodo;
