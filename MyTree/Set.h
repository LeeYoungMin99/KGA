#pragma once


#include <utility>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template<typename T>
class Set
{
	struct Node
	{
		Node(const T& data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
			:Data{ data }, Parent{ parent }, Left{ left }, Right{ right }{}
		Node(const Node& other) = delete;
		Node& operator=(const Node& rhs) = delete;
		~Node() { Parent = Left = Right = nullptr; }

		T		Data;
		Node* Parent = nullptr;
		Node* Left = nullptr;
		Node* Right = nullptr;
	};


public:
	~Set()
	{
		clear();
	}

	int	height() const
	{
		if (empty())
		{
			return -1;
		}

		queue<Node*> q;
		q.push(_root);

		int h = -1;

		while (false == q.empty())
		{
			size_t sz = q.size();
			for (size_t i = 0; i < sz; ++i)
			{
				Node* node = q.front();
				q.pop();

				if (node->Left)
				{
					q.push(node->Left);
				}
				if (node->Right)
				{
					q.push(node->Right);
				}
			}

			++h;
		}

		return h;
	}

	int	height2() const
	{
		if (empty())
		{
			return -1;
		}

		stack<pair<int, Node*>> s;
		s.emplace(0, _root);

		int result = 0;

		while (false == s.empty())
		{
			Node* node = s.top().second;
			int h = s.top().first;
			s.pop();

			if (node->Right)
			{
				s.emplace(h + 1, node->Right);
			}

			if (node->Left)
			{
				s.emplace(h + 1, node->Left);
			}

			if (result < h)
				result = h;
		}

		return result;
	}

	int	height3() const
	{
		return heightHelper(_root);
	}

	bool empty() const { return _root == nullptr; }

	size_t size() const { return _size; }

	void clear()
	{
		while (false == empty())
		{
			erase(_root);
		}
	}

	// 트리에 값을 삽입한다. insert
	pair<Node*, bool>	insert(const T& value)
	{
		if (empty())
		{
			_root = new Node(value);
			++_size;

			return make_pair(_root, true);
		}

		Node* inserted = _root;
		Node* parent = nullptr;

		while (inserted)
		{
			parent = inserted;

			if (inserted->Data == value)
			{
				return make_pair(inserted, false);
			}
			else if (inserted->Data < value)
			{
				inserted = inserted->Right;
			}
			else
			{
				inserted = inserted->Left;
			}
		}

		inserted = new Node(value, parent);

		if (parent->Data > value)
		{
			parent->Left = inserted;
		}
		else
		{
			parent->Right = inserted;
		}

		++_size;

		return make_pair(inserted, true);
	}

	// 트리에서 값을 삭제한다 erase
	void				erase(Node* pos)
	{
		if (empty())
		{
			return;
		}

		if (pos ->Parent == nullptr)
		{
			if (pos->Left == nullptr && pos->Right == nullptr)
			{
				_root = nullptr;

				delete pos;
				pos = nullptr;

				--_size;

				return;
			}

			if (pos->Left == nullptr)
			{
				_root = pos->Right;
				_root->Parent = nullptr;

				delete pos;
				pos = nullptr;

				--_size;

				return;
			}
			else if(pos->Right == nullptr)
			{
				_root = pos->Left;
				_root->Parent = nullptr;

				delete pos;
				pos = nullptr;

				--_size;

				return;
			}


			Node* successor = pos->Left;
			while (successor->Right)
			{
				successor = successor->Right;
			}

			swap(pos->Data, successor->Data);

			erase(successor);

			return;
		}

		// 자식이 없을때 => 단말 노드일떄
		if (pos->Left == nullptr && pos->Right == nullptr)
		{
			if (pos->Parent->Left == pos)
			{
				pos->Parent->Left = nullptr;
			}
			else
			{
				pos->Parent->Right = nullptr;
			}

			delete pos;
			pos = nullptr;

			--_size;

			return;
		}


		// 자식이 하나일 때
		if (pos->Left == nullptr)
		{
			if (pos->Parent->Left == pos)
			{
				pos->Parent->Left = pos->Right;
			}
			else
			{
				pos->Parent->Right = pos->Right;
			}

			pos->Right->Parent = pos->Parent;

			delete pos;
			pos = nullptr;

			--_size;
			
			return;
		}
		else if (pos->Right == nullptr)
		{
			if (pos->Parent->Left == pos)
			{
				pos->Parent->Left = pos->Left;
			}
			else
			{
				pos->Parent->Right = pos->Left;
			}

			pos->Left->Parent = pos->Parent;

			delete pos;
			pos = nullptr;

			--_size;

			return;
		}

		// 자식이 2개일 때
		Node* successor = pos->Left;
		
		while (successor->Right)
		{
			successor = successor->Right;
		}
		
		swap(pos->Data, successor->Data);
		
		erase(successor);
		
		return;

		Node* successor2 = pos->Right;

		while (successor2->Left)
		{
			successor2 = successor2->Left;
		}

		swap(pos->Data, successor2->Data);

		erase(successor2);

		return;
	}

	size_t				erase(const T& value)
	{
		Node* removed = find(value);
		if (removed == nullptr)
		{
			return 0;
		}

		erase(removed);

		return 1;
	}

	// 트리에서 특정 값을 찾는다. find
	//원래는 못찾으면 end()를 반환하지만 우리는 nullptr을 반환
	Node* find(const T& value)
	{
		return const_cast<Node*>(static_cast<const Set&>(*this).find(value));
	}

	const Node* find(const T& value) const
	{
		const Node* result = _root;

		while (result)
		{
			if (result->Data == value)
			{
				return result;
			}
			else if (result->Data < value)
			{
				result = result->Right;
			}
			else if (result->Data > value)
			{
				result = result->Left;
			}
		}

		return result;
	}

	// 순회
	void				traverseByPreorder() { PreorderHelper(_root); }
	void				traverseByInorder() { InorderHelper(_root); }
	void				traverseByPostorder() { PostorderHelper(_root); }
	void				traverseByLevelorder()
	{
		if (empty())
		{
			return;
		}

		queue<Node*> q;
		q.push(_root);

		int level = 0;
		while (false == q.empty())
		{
			size_t sz = q.size();
			cout << "Level" << level << " : ";

			for (size_t i = 0; i < sz; ++i)
			{
				Node* node = q.front();
				q.pop();

				cout << node->Data << " ";

				if (node->Left)
				{
					q.push(node->Left);
				}

				if (node->Right)
				{
					q.push(node->Right);
				}
			}

			++level;
			cout << "\n";
		}
	}

private:
	int heightHelper(const Node* node) const
	{
		if (node == nullptr)
		{
			return -1;
		}

		int left = heightHelper(node->Left) + 1;
		int right = heightHelper(node->Right) + 1;

		return max(left, right);
	}

	void PreorderHelper(const Node* node)
	{
		if (node == nullptr)
		{
			return;
		}

		cout << node->Data << " ";

		if (node->Left)
		{
			PreorderHelper(node->Left);
		}

		if (node->Right)
		{
			PreorderHelper(node->Right);
		}
	}

	void InorderHelper(const Node* node)
	{
		if (node == nullptr)
		{
			return;
		}

		if (node->Left)
		{
			InorderHelper(node->Left);
		}

		cout << node->Data << " ";

		if (node->Right)
		{
			InorderHelper(node->Right);
		}
	}

	void PostorderHelper(const Node* node)
	{
		if (node == nullptr)
		{
			return;
		}

		if (node->Left)
		{
			PostorderHelper(node->Left);
		}

		if (node->Right)
		{
			PostorderHelper(node->Right);
		}

		cout << node->Data << " ";

	}

public:
protected:
private:
	Node* _root = nullptr;
	size_t _size = 0;
};