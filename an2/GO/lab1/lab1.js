// Lab 1 - HTTP fundamentals cu JavaScript (fetch)
// Ruleaza cu: node lab1.js
// Necesita Node.js versiunea 18 sau mai noua 

async function getPost() {
  console.log('--- GET /posts/1 ---');
  const response = await fetch('https://jsonplaceholder.typicode.com/posts/1');
  console.log('Status:', response.status);
  const data = await response.json();
  console.log(data);
}

async function createPost() {
  console.log('--- POST /posts ---');
  const response = await fetch('https://jsonplaceholder.typicode.com/posts', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({
      title: 'Prima postare de test',
      body: 'Acesta este un exemplu de continut trimis printr-un POST.',
      userId: 7
    })
  });
  console.log('Status:', response.status);
  const data = await response.json();
  console.log(data);
}

async function deletePost() {
  console.log('--- DELETE /posts/1 ---');
  const response = await fetch('https://jsonplaceholder.typicode.com/posts/1', {
    method: 'DELETE'
  });
  console.log('Status:', response.status);
}

async function main() {
  await getPost();
  await createPost();
  await deletePost();
}

main();