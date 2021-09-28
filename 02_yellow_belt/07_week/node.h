#pragma once

#include "date.h"

#include <string>
#include <memory>



enum class Comparison {
	Less,
	LessOrEqual,
	Equal,
	NotEqual,
	Greater,
	GreaterOrEqual,
};

enum class LogicalOperation {
	And,
	Or,
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const std::string& event) const override;
};

// DateComparisonNode class

class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison comparison, const Date& date);
	bool Evaluate(const Date& date, const std::string& event) const override;

private:
	Comparison comparison_;
	Date date_;
};

// EventComparisonNode class

class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison comparison, const std::string& event);
	bool Evaluate(const Date& date, const std::string& event) const override;

private:
	Comparison comparison_;
	std::string event_;
};

// LogicalOperationNode class

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(LogicalOperation operation, std::shared_ptr<Node> left,
		std::shared_ptr<Node> right);
	bool Evaluate(const Date& date, const std::string& event) const override;

private:
	LogicalOperation operation_;
	std::shared_ptr<Node> left_, right_;
};

// Tests
void TestDateComparisonNode();
void TestEventComparisonNode();
void TestLogicalOperationNode();