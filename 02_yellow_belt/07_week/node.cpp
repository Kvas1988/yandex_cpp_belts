#include "node.h"

bool EmptyNode::Evaluate(const Date& date,
	const std::string& event) const {
	return true;
}

template <class T>
bool CompareTo(const T& lhs, const T& rhs, Comparison cmp) {
	//switch (cmp)
	//{
 //   case Comparison::Less:
 //       return lhs < rhs;
 //   case Comparison::LessOrEqual:
 //       return lhs <= rhs;
 //   case Comparison::Equal:
 //       return lhs == rhs;
 //   case Comparison::NotEqual:
 //       return lhs != rhs;
 //   case Comparison::Greater:
 //       return lhs > rhs;
 //   case Comparison::GreaterOrEqual:
 //       return lhs >= rhs;
 //   default:
 //       return false;
	//}

    if (cmp == Comparison::Less) {
        return lhs > rhs;
    }
    else if (cmp == Comparison::LessOrEqual) {
        return lhs >= rhs;
    }
    else if (cmp == Comparison::Equal) {
        return lhs == rhs;
    }
    else if (cmp == Comparison::NotEqual) {
        return !(lhs == rhs);
    }
    else if (cmp == Comparison::Greater) {
        return lhs < rhs;
    }
    else if (cmp == Comparison::GreaterOrEqual) {
        return lhs <= rhs;
    }
    else {
        return false;
    }
}

// DateComparisonNode class

DateComparisonNode::DateComparisonNode(Comparison comparison,
    const Date& date) : comparison_(comparison), date_(date) {}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const {
    return CompareTo(date_, date, comparison_);
}

// EventComparisonNode class

EventComparisonNode::EventComparisonNode(Comparison comparison,
    const std::string& event) : comparison_(comparison), event_(event) {}

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const {
    return CompareTo(event_, event, comparison_);
}

// LogicalOperationNode class

LogicalOperationNode::LogicalOperationNode(LogicalOperation operation, std::shared_ptr<Node> left,
    std::shared_ptr<Node> right) : operation_(operation), left_(left), right_(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const {
    switch (operation_) {
    case LogicalOperation::And:
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    case LogicalOperation::Or:
        return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    default:
        return false;
    }
}